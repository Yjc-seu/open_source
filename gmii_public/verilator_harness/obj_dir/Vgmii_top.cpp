// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgmii_top.h for the primary calling header

#include "Vgmii_top.h"
#include "Vgmii_top__Syms.h"

//==========

void Vgmii_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vgmii_top::eval\n"); );
    Vgmii_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/gmii_public/verilator_harness/../dut/gmii_top.v", 48, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vgmii_top::_eval_initial_loop(Vgmii_top__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/gmii_public/verilator_harness/../dut/gmii_top.v", 48, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vgmii_top::_combo__TOP__29(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_combo__TOP__29\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->gmii_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->gmii_top__DOT__tx_send = vlTOPp->tx_send;
    vlTOPp->gmii_top__DOT__tx_byte = vlTOPp->tx_byte;
    vlTOPp->gmii_top__DOT__tx_tready = vlTOPp->tx_tready;
    vlTOPp->gmii_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->gmii_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->gmii_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->gmii_top__DOT__gmii_rxd = vlTOPp->gmii_rxd;
    vlTOPp->gmii_top__DOT__gmii_rx_dv = vlTOPp->gmii_rx_dv;
    vlTOPp->gmii_top__DOT__gmii_rx_er = vlTOPp->gmii_rx_er;
    vlTOPp->cov_tready = vlTOPp->tx_tready;
    vlTOPp->gmii_top__DOT__clk = vlTOPp->clk;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd = vlTOPp->gmii_top__DOT__gmii_rxd;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv = vlTOPp->gmii_top__DOT__gmii_rx_dv;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er = vlTOPp->gmii_top__DOT__gmii_rx_er;
    vlTOPp->gmii_top__DOT__cov_tready = vlTOPp->cov_tready;
    vlTOPp->gmii_top__DOT__u_rx__DOT__clk = vlTOPp->gmii_top__DOT__clk;
    vlTOPp->gmii_top__DOT__u_tx__DOT__clk = vlTOPp->gmii_top__DOT__clk;
}

VL_INLINE_OPT void Vgmii_top::_sequent__TOP__30(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_sequent__TOP__30\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[0U] 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_next[0U];
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[1U] 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_next[1U];
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[2U] 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_next[2U];
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_tag_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_tag_next;
    vlTOPp->gmii_top__DOT__u_tx__DOT__mii_msn_reg = vlTOPp->gmii_top__DOT__u_tx__DOT__mii_msn_next;
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next;
    vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_reg = vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser_reg 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__mii_odd = 0U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tdata_reg 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tdata_next;
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_next;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast_reg 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast_next;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_valid_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_valid_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_valid_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_int_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_int_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_int_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid_reg 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_next;
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_reg = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet_reg = 0U;
    if (vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet_int_reg) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__ptp_ts_reg[0U] = 0U;
        vlTOPp->gmii_top__DOT__u_rx__DOT__ptp_ts_reg[1U] = 0U;
        vlTOPp->gmii_top__DOT__u_rx__DOT__ptp_ts_reg[2U] = 0U;
        vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet_reg = 1U;
    }
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next;
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs_reg 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_reg 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_reg 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg = vlTOPp->gmii_top__DOT__u_rx__DOT__state_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg = vlTOPp->gmii_top__DOT__u_tx__DOT__state_next;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg = 0U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4 
        = ((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d3) 
           & (IData)(vlTOPp->gmii_rx_dv));
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4 = 0U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d3;
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg = vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next;
    if (vlTOPp->gmii_top__DOT__u_tx__DOT__reset_crc) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state = 0xffffffffU;
    } else {
        if (vlTOPp->gmii_top__DOT__u_tx__DOT__update_crc) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state 
                = vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next;
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4 = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d3;
    if (vlTOPp->gmii_top__DOT__u_rx__DOT__reset_crc) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state = 0xffffffffU;
    } else {
        if (vlTOPp->gmii_top__DOT__u_rx__DOT__update_crc) {
            vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state 
                = vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next;
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_next[0U] 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[0U];
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_next[1U] 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[1U];
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_next[2U] 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[2U];
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_tag_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_tag_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__mii_msn_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__mii_msn_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd = vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_reg;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser_reg;
    vlTOPp->gmii_top__DOT__rx_core_tdata = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tdata_reg;
    vlTOPp->gmii_top__DOT__rx_core_tlast = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_int_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_int_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er = vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en = vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_reg;
    vlTOPp->gmii_top__DOT__rx_core_tvalid = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid_reg;
    vlTOPp->gmii_top__DOT__tx_core_start_packet = vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_reg;
    vlTOPp->gmii_top__DOT__tx_core_underflow = vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow_reg;
    vlTOPp->gmii_top__DOT__rx_core_start_packet = vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet_reg;
    vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet_int_reg = 0U;
    if (vlTOPp->gmii_top__DOT__u_rx__DOT__in_frame) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__in_frame 
            = vlTOPp->gmii_rx_dv;
    } else {
        if (((IData)(vlTOPp->gmii_rx_dv) & (0xd5U == (IData)(vlTOPp->gmii_rxd)))) {
            vlTOPp->gmii_top__DOT__u_rx__DOT__in_frame = 1U;
            vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet_int_reg = 1U;
        }
    }
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet_int_reg = 0U;
        vlTOPp->gmii_top__DOT__u_rx__DOT__in_frame = 0U;
    }
    vlTOPp->gmii_top__DOT__rx_core_bad_fcs = vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs_reg;
    vlTOPp->gmii_top__DOT__tx_core_tready = vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_reg;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid_next = 1U;
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__update_crc = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_rx__DOT__update_crc = 1U;
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__reset_crc = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__reset_crc = 1U;
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__reset_crc = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__reset_crc = 1U;
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__reset_crc = 1U;
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__update_crc = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__update_crc = 1U;
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__update_crc = 1U;
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__update_crc = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_next = 0x3bU;
    } else {
        if ((1U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_next 
                        = (0x3fU & ((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg) 
                                    - (IData)(1U)));
                }
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_next 
                            = (0x3fU & ((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg) 
                                        - (IData)(1U)));
                    }
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_next 
                                = (0x3fU & ((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg) 
                                            - (IData)(1U)));
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((6U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_next = 1U;
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((2U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                if ((3U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    if ((4U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er_next 
                                = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_reg;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next = 1U;
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next 
                = (0xffU & ((IData)(1U) + (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg)));
            if ((6U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next = 0U;
                }
            }
        } else {
            if ((2U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    if ((1U & (~ (IData)((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg)))))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next = 0U;
                    }
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        if ((1U & (~ (IData)((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg)))))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next = 0U;
                        }
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next 
                                = (0xffU & ((IData)(1U) 
                                            + (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg)));
                            if ((3U <= (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next = 0U;
                            }
                        } else {
                            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next 
                                    = (0xffU & ((IData)(1U) 
                                                + (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg)));
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d3 
        = ((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d2) 
           & (IData)(vlTOPp->gmii_rx_dv));
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d3 = 0U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d3 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d2;
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_in 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__state_in 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state;
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfeU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (1U & VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                   << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                 & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__0__KET____DOT__mask))));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfdU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (2U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__1__KET____DOT__mask)) 
                    << 1U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfbU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (4U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__2__KET____DOT__mask)) 
                    << 2U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xf7U & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (8U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__3__KET____DOT__mask)) 
                    << 3U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xefU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x10U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__4__KET____DOT__mask)) 
                       << 4U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xdfU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x20U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__5__KET____DOT__mask)) 
                       << 5U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xbfU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x40U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__6__KET____DOT__mask)) 
                       << 6U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0x7fU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x80U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__7__KET____DOT__mask)) 
                       << 7U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffffeU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (1U 
                                                     & VL_REDXOR_64(
                                                                    ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                       << 0x20U) 
                                                                      | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                     & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__0__KET____DOT__mask))));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffffdU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (2U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__1__KET____DOT__mask)) 
                                                        << 1U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffffbU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (4U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__2__KET____DOT__mask)) 
                                                        << 2U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffff7U 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (8U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__3__KET____DOT__mask)) 
                                                        << 3U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffffefU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x10U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__4__KET____DOT__mask)) 
                                                        << 4U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffffdfU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x20U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__5__KET____DOT__mask)) 
                                                        << 5U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffffbfU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x40U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__6__KET____DOT__mask)) 
                                                        << 6U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffff7fU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x80U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__7__KET____DOT__mask)) 
                                                        << 7U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffeffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x100U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__8__KET____DOT__mask)) 
                                                        << 8U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffdffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x200U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__9__KET____DOT__mask)) 
                                                        << 9U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffbffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x400U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__10__KET____DOT__mask)) 
                                                        << 0xaU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffff7ffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x800U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__11__KET____DOT__mask)) 
                                                        << 0xbU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffefffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x1000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__12__KET____DOT__mask)) 
                                                        << 0xcU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffdfffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x2000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__13__KET____DOT__mask)) 
                                                        << 0xdU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffbfffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x4000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__14__KET____DOT__mask)) 
                                                        << 0xeU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffff7fffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x8000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__15__KET____DOT__mask)) 
                                                        << 0xfU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffeffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x10000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__16__KET____DOT__mask)) 
                                                        << 0x10U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffdffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x20000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__17__KET____DOT__mask)) 
                                                        << 0x11U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffbffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x40000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__18__KET____DOT__mask)) 
                                                        << 0x12U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfff7ffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x80000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__19__KET____DOT__mask)) 
                                                        << 0x13U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffefffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x100000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__20__KET____DOT__mask)) 
                                                        << 0x14U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffdfffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x200000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__21__KET____DOT__mask)) 
                                                        << 0x15U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffbfffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x400000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__22__KET____DOT__mask)) 
                                                        << 0x16U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xff7fffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x800000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__23__KET____DOT__mask)) 
                                                        << 0x17U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfeffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x1000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__24__KET____DOT__mask)) 
                                                        << 0x18U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfdffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x2000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__25__KET____DOT__mask)) 
                                                        << 0x19U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfbffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x4000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__26__KET____DOT__mask)) 
                                                        << 0x1aU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xf7ffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x8000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__27__KET____DOT__mask)) 
                                                        << 0x1bU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xefffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x10000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__28__KET____DOT__mask)) 
                                                        << 0x1cU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xdfffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x20000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__29__KET____DOT__mask)) 
                                                        << 0x1dU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xbfffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x40000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__30__KET____DOT__mask)) 
                                                        << 0x1eU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0x7fffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x80000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__31__KET____DOT__mask)) 
                                                        << 0x1fU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d3 = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d2;
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_in 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tdata_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tdata_next 
                = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4;
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__state_in 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state;
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfeU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (1U & VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                   << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                 & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__0__KET____DOT__mask))));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfdU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (2U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__1__KET____DOT__mask)) 
                    << 1U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfbU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (4U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__2__KET____DOT__mask)) 
                    << 2U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xf7U & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (8U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__3__KET____DOT__mask)) 
                    << 3U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xefU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x10U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__4__KET____DOT__mask)) 
                       << 4U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xdfU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x20U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__5__KET____DOT__mask)) 
                       << 5U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xbfU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x40U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__6__KET____DOT__mask)) 
                       << 6U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0x7fU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x80U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__7__KET____DOT__mask)) 
                       << 7U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffffeU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (1U 
                                                     & VL_REDXOR_64(
                                                                    ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                       << 0x20U) 
                                                                      | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                     & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__0__KET____DOT__mask))));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffffdU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (2U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__1__KET____DOT__mask)) 
                                                        << 1U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffffbU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (4U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__2__KET____DOT__mask)) 
                                                        << 2U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffff7U 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (8U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__3__KET____DOT__mask)) 
                                                        << 3U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffffefU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x10U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__4__KET____DOT__mask)) 
                                                        << 4U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffffdfU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x20U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__5__KET____DOT__mask)) 
                                                        << 5U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffffbfU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x40U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__6__KET____DOT__mask)) 
                                                        << 6U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffff7fU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x80U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__7__KET____DOT__mask)) 
                                                        << 7U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffeffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x100U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__8__KET____DOT__mask)) 
                                                        << 8U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffdffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x200U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__9__KET____DOT__mask)) 
                                                        << 9U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffbffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x400U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__10__KET____DOT__mask)) 
                                                        << 0xaU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffff7ffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x800U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__11__KET____DOT__mask)) 
                                                        << 0xbU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffefffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x1000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__12__KET____DOT__mask)) 
                                                        << 0xcU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffdfffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x2000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__13__KET____DOT__mask)) 
                                                        << 0xdU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffbfffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x4000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__14__KET____DOT__mask)) 
                                                        << 0xeU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffff7fffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x8000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__15__KET____DOT__mask)) 
                                                        << 0xfU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffeffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x10000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__16__KET____DOT__mask)) 
                                                        << 0x10U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffdffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x20000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__17__KET____DOT__mask)) 
                                                        << 0x11U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffbffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x40000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__18__KET____DOT__mask)) 
                                                        << 0x12U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfff7ffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x80000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__19__KET____DOT__mask)) 
                                                        << 0x13U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffefffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x100000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__20__KET____DOT__mask)) 
                                                        << 0x14U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffdfffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x200000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__21__KET____DOT__mask)) 
                                                        << 0x15U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffbfffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x400000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__22__KET____DOT__mask)) 
                                                        << 0x16U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xff7fffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x800000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__23__KET____DOT__mask)) 
                                                        << 0x17U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfeffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x1000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__24__KET____DOT__mask)) 
                                                        << 0x18U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfdffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x2000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__25__KET____DOT__mask)) 
                                                        << 0x19U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfbffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x4000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__26__KET____DOT__mask)) 
                                                        << 0x1aU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xf7ffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x8000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__27__KET____DOT__mask)) 
                                                        << 0x1bU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xefffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x10000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__28__KET____DOT__mask)) 
                                                        << 0x1cU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xdfffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x20000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__29__KET____DOT__mask)) 
                                                        << 0x1dU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xbfffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x40000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__30__KET____DOT__mask)) 
                                                        << 0x1eU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0x7fffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x80000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__31__KET____DOT__mask)) 
                                                        << 0x1fU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tdata 
        = vlTOPp->gmii_top__DOT__rx_core_tdata;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast 
        = vlTOPp->gmii_top__DOT__rx_core_tlast;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid 
        = vlTOPp->gmii_top__DOT__rx_core_tvalid;
    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet 
        = vlTOPp->gmii_top__DOT__tx_core_start_packet;
    vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow 
        = vlTOPp->gmii_top__DOT__tx_core_underflow;
    vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet 
        = vlTOPp->gmii_top__DOT__rx_core_start_packet;
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs 
        = vlTOPp->gmii_top__DOT__rx_core_bad_fcs;
    vlTOPp->cov_bad_fcs = vlTOPp->gmii_top__DOT__rx_core_bad_fcs;
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready 
        = vlTOPp->gmii_top__DOT__tx_core_tready;
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__state_out 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next;
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__state_out 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next;
    vlTOPp->gmii_top__DOT__cov_bad_fcs = vlTOPp->cov_bad_fcs;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d2 
        = ((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d1) 
           & (IData)(vlTOPp->gmii_rx_dv));
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d2 = 0U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d2 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d1;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d2 = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d1;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d1 
        = ((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d0) 
           & (IData)(vlTOPp->gmii_rx_dv));
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d1 = 0U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d1 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d0;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d1 = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d0;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d0 
        = vlTOPp->gmii_rx_dv;
    if (vlTOPp->gmii_top__DOT__rst) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d0 = 0U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d0 
        = vlTOPp->gmii_rx_er;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d0 = vlTOPp->gmii_rxd;
}

VL_INLINE_OPT void Vgmii_top::_sequent__TOP__31(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_sequent__TOP__31\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*4:0*/ __Vdly__gmii_top__DOT__s8_cnt;
    CData/*2:0*/ __Vdly__gmii_top__DOT__s7_gap;
    CData/*3:0*/ __Vdly__gmii_top__DOT__s5_cnt;
    CData/*0:0*/ __Vdly__gmii_top__DOT__s1a;
    CData/*0:0*/ __Vdly__gmii_top__DOT__s1b;
    CData/*3:0*/ __Vdly__gmii_top__DOT__rd_ptr;
    CData/*0:0*/ __Vdly__gmii_top__DOT__s2a;
    CData/*0:0*/ __Vdly__gmii_top__DOT__s2b;
    CData/*0:0*/ __Vdly__gmii_top__DOT__s2c;
    CData/*0:0*/ __Vdly__gmii_top__DOT__s2d;
    CData/*3:0*/ __Vdly__gmii_top__DOT__s9_cnt;
    CData/*3:0*/ __Vdlyvdim0__gmii_top__DOT__fifo__v0;
    CData/*7:0*/ __Vdlyvval__gmii_top__DOT__fifo__v0;
    CData/*0:0*/ __Vdlyvset__gmii_top__DOT__fifo__v0;
    CData/*3:0*/ __Vdly__gmii_top__DOT__wr_ptr;
    CData/*3:0*/ __Vdlyvdim0__gmii_top__DOT__fifo__v1;
    CData/*7:0*/ __Vdlyvval__gmii_top__DOT__fifo__v1;
    CData/*0:0*/ __Vdlyvset__gmii_top__DOT__fifo__v1;
    CData/*0:0*/ __Vdly__gmii_top__DOT__s10_armed;
    CData/*1:0*/ __Vdly__gmii_top__DOT__s10_cnt;
    CData/*4:0*/ __Vdly__gmii_top__DOT__fifo_cnt;
    CData/*3:0*/ __Vdly__gmii_top__DOT__s3_cnt;
    CData/*0:0*/ __Vdly__gmii_top__DOT__s3_armed;
    CData/*1:0*/ __Vdly__gmii_top__DOT__hld_class;
    CData/*1:0*/ __Vdly__gmii_top__DOT__hld_state;
    SData/*15:0*/ __Vdly__cov_frame_len;
    SData/*15:0*/ __Vdly__gmii_top__DOT__hld_cnt;
    // Body
    __Vdly__gmii_top__DOT__s9_cnt = vlTOPp->gmii_top__DOT__s9_cnt;
    __Vdly__gmii_top__DOT__s7_gap = vlTOPp->gmii_top__DOT__s7_gap;
    __Vdly__gmii_top__DOT__s10_cnt = vlTOPp->gmii_top__DOT__s10_cnt;
    __Vdly__gmii_top__DOT__s10_armed = vlTOPp->gmii_top__DOT__s10_armed;
    __Vdly__gmii_top__DOT__s8_cnt = vlTOPp->gmii_top__DOT__s8_cnt;
    __Vdly__gmii_top__DOT__s1b = vlTOPp->gmii_top__DOT__s1b;
    __Vdly__gmii_top__DOT__s1a = vlTOPp->gmii_top__DOT__s1a;
    __Vdly__gmii_top__DOT__rd_ptr = vlTOPp->gmii_top__DOT__rd_ptr;
    __Vdly__cov_frame_len = vlTOPp->cov_frame_len;
    __Vdly__gmii_top__DOT__hld_cnt = vlTOPp->gmii_top__DOT__hld_cnt;
    __Vdly__gmii_top__DOT__hld_state = vlTOPp->gmii_top__DOT__hld_state;
    __Vdly__gmii_top__DOT__hld_class = vlTOPp->gmii_top__DOT__hld_class;
    __Vdly__gmii_top__DOT__wr_ptr = vlTOPp->gmii_top__DOT__wr_ptr;
    __Vdly__gmii_top__DOT__s3_armed = vlTOPp->gmii_top__DOT__s3_armed;
    __Vdly__gmii_top__DOT__s3_cnt = vlTOPp->gmii_top__DOT__s3_cnt;
    __Vdly__gmii_top__DOT__s2d = vlTOPp->gmii_top__DOT__s2d;
    __Vdly__gmii_top__DOT__s2c = vlTOPp->gmii_top__DOT__s2c;
    __Vdly__gmii_top__DOT__s2b = vlTOPp->gmii_top__DOT__s2b;
    __Vdly__gmii_top__DOT__s2a = vlTOPp->gmii_top__DOT__s2a;
    __Vdlyvset__gmii_top__DOT__fifo__v0 = 0U;
    __Vdlyvset__gmii_top__DOT__fifo__v1 = 0U;
    __Vdly__gmii_top__DOT__fifo_cnt = vlTOPp->gmii_top__DOT__fifo_cnt;
    __Vdly__gmii_top__DOT__s5_cnt = vlTOPp->gmii_top__DOT__s5_cnt;
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq9 = 0U;
        if (vlTOPp->gmii_top__DOT__idle_all) {
            if ((0xfU > (IData)(vlTOPp->gmii_top__DOT__s9_cnt))) {
                __Vdly__gmii_top__DOT__s9_cnt = (0xfU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->gmii_top__DOT__s9_cnt)));
            }
            if ((2U <= (IData)(vlTOPp->gmii_top__DOT__s9_cnt))) {
                vlTOPp->cov_seq9 = 1U;
            }
        } else {
            __Vdly__gmii_top__DOT__s9_cnt = 0U;
        }
    } else {
        __Vdly__gmii_top__DOT__s9_cnt = 0U;
        vlTOPp->cov_seq9 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq7 = 0U;
        if (vlTOPp->gmii_top__DOT__tx_done_evt) {
            __Vdly__gmii_top__DOT__s7_gap = 0U;
        } else {
            if ((7U > (IData)(vlTOPp->gmii_top__DOT__s7_gap))) {
                __Vdly__gmii_top__DOT__s7_gap = (7U 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->gmii_top__DOT__s7_gap)));
            }
        }
        if (((IData)(vlTOPp->gmii_top__DOT__frame_start) 
             & (2U >= (IData)(vlTOPp->gmii_top__DOT__s7_gap)))) {
            vlTOPp->cov_seq7 = 1U;
        }
    } else {
        vlTOPp->cov_seq7 = 0U;
        __Vdly__gmii_top__DOT__s7_gap = 7U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq10 = 0U;
        if (vlTOPp->gmii_top__DOT__tx_done_evt) {
            __Vdly__gmii_top__DOT__s10_armed = 1U;
            __Vdly__gmii_top__DOT__s10_cnt = 0U;
        } else {
            if (vlTOPp->gmii_top__DOT__s10_armed) {
                if (vlTOPp->gmii_top__DOT__idle_all) {
                    if ((2U >= (IData)(vlTOPp->gmii_top__DOT__s10_cnt))) {
                        vlTOPp->cov_seq10 = 1U;
                    }
                    __Vdly__gmii_top__DOT__s10_armed = 0U;
                } else {
                    if ((3U > (IData)(vlTOPp->gmii_top__DOT__s10_cnt))) {
                        __Vdly__gmii_top__DOT__s10_cnt 
                            = (3U & ((IData)(1U) + (IData)(vlTOPp->gmii_top__DOT__s10_cnt)));
                    }
                    if ((2U <= (IData)(vlTOPp->gmii_top__DOT__s10_cnt))) {
                        __Vdly__gmii_top__DOT__s10_armed = 0U;
                    }
                }
            }
        }
    } else {
        vlTOPp->cov_seq10 = 0U;
        __Vdly__gmii_top__DOT__s10_armed = 0U;
        __Vdly__gmii_top__DOT__s10_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq8 = 0U;
        if (vlTOPp->cov_busy) {
            if ((0x1fU > (IData)(vlTOPp->gmii_top__DOT__s8_cnt))) {
                __Vdly__gmii_top__DOT__s8_cnt = (0x1fU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->gmii_top__DOT__s8_cnt)));
            }
            if ((7U <= (IData)(vlTOPp->gmii_top__DOT__s8_cnt))) {
                vlTOPp->cov_seq8 = 1U;
            }
        } else {
            __Vdly__gmii_top__DOT__s8_cnt = 0U;
        }
    } else {
        __Vdly__gmii_top__DOT__s8_cnt = 0U;
        vlTOPp->cov_seq8 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq4 = 0U;
        if (((IData)(vlTOPp->gmii_top__DOT__s4a) & (IData)(vlTOPp->gmii_top__DOT__rx_core_bad_frame))) {
            vlTOPp->cov_seq4 = 1U;
            vlTOPp->gmii_top__DOT__s4a = 0U;
        } else {
            if (((IData)(vlTOPp->gmii_rx_dv) & (IData)(vlTOPp->gmii_rx_er))) {
                vlTOPp->gmii_top__DOT__s4a = 1U;
            }
        }
    } else {
        vlTOPp->gmii_top__DOT__s4a = 0U;
        vlTOPp->cov_seq4 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->gmii_top__DOT__fp = vlTOPp->gmii_top__DOT__fp_next;
        vlTOPp->gmii_top__DOT__min_cnt = vlTOPp->gmii_top__DOT__min_cnt_next;
    } else {
        vlTOPp->gmii_top__DOT__fp = 0U;
        vlTOPp->gmii_top__DOT__min_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_rx_err = (((IData)(vlTOPp->gmii_top__DOT__rx_dv_prev) 
                               & (~ (IData)(vlTOPp->gmii_rx_dv))) 
                              & (IData)(vlTOPp->gmii_top__DOT__er_seen));
        vlTOPp->cov_seq1 = 0U;
        if ((((IData)(vlTOPp->gmii_top__DOT__s1b) & (IData)(vlTOPp->gmii_top__DOT__rx_dv_prev)) 
             & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
            vlTOPp->cov_seq1 = 1U;
            __Vdly__gmii_top__DOT__s1a = 0U;
            __Vdly__gmii_top__DOT__s1b = 0U;
        } else {
            if ((((IData)(vlTOPp->gmii_top__DOT__s1a) 
                  & (IData)(vlTOPp->gmii_rx_dv)) & 
                 (0xd5U == (IData)(vlTOPp->gmii_rxd)))) {
                __Vdly__gmii_top__DOT__s1a = 0U;
                __Vdly__gmii_top__DOT__s1b = 1U;
            } else {
                if (((IData)(vlTOPp->gmii_top__DOT__rx_dv_prev) 
                     & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    __Vdly__gmii_top__DOT__s1a = 0U;
                    __Vdly__gmii_top__DOT__s1b = 0U;
                } else {
                    if ((((IData)(vlTOPp->gmii_rx_dv) 
                          & (0x55U == (IData)(vlTOPp->gmii_rxd))) 
                         & (~ (IData)(vlTOPp->gmii_top__DOT__s1b)))) {
                        __Vdly__gmii_top__DOT__s1a = 1U;
                    }
                }
            }
        }
        if (((IData)(vlTOPp->gmii_rx_dv) & (IData)(vlTOPp->gmii_rx_er))) {
            vlTOPp->gmii_top__DOT__er_seen = 1U;
        } else {
            if (((IData)(vlTOPp->gmii_top__DOT__rx_dv_prev) 
                 & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                vlTOPp->gmii_top__DOT__er_seen = 0U;
            }
        }
    } else {
        vlTOPp->gmii_top__DOT__er_seen = 0U;
        vlTOPp->cov_rx_err = 0U;
        vlTOPp->cov_seq1 = 0U;
        __Vdly__gmii_top__DOT__s1a = 0U;
        __Vdly__gmii_top__DOT__s1b = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->gmii_top__DOT__cfg_ok) {
            if ((0U == (IData)(vlTOPp->cfg_sel))) {
                vlTOPp->gmii_top__DOT__cfg_ifg = vlTOPp->cfg_data;
            }
        }
    } else {
        vlTOPp->gmii_top__DOT__cfg_ifg = 0xcU;
    }
    vlTOPp->gmii_top__DOT__er_d4 = ((IData)(vlTOPp->rst_n) 
                                    & (IData)(vlTOPp->gmii_top__DOT__er_d3));
    vlTOPp->gmii_top__DOT__dv_d4 = ((IData)(vlTOPp->rst_n) 
                                    & ((IData)(vlTOPp->gmii_top__DOT__dv_d3) 
                                       & (IData)(vlTOPp->gmii_rx_dv)));
    if (vlTOPp->rst_n) {
        if (vlTOPp->gmii_top__DOT__pop_evt) {
            __Vdly__gmii_top__DOT__rd_ptr = (0xfU & 
                                             ((IData)(1U) 
                                              + (IData)(vlTOPp->gmii_top__DOT__rd_ptr)));
            vlTOPp->cov_tx_byte = vlTOPp->gmii_top__DOT__fifo
                [vlTOPp->gmii_top__DOT__rd_ptr];
        }
        if (((IData)(vlTOPp->gmii_top__DOT__pop_evt) 
             & (IData)(vlTOPp->gmii_top__DOT__tlast_comb))) {
            vlTOPp->gmii_top__DOT__hold_byte = vlTOPp->gmii_top__DOT__fifo
                [vlTOPp->gmii_top__DOT__rd_ptr];
        }
    } else {
        __Vdly__gmii_top__DOT__rd_ptr = 0U;
        vlTOPp->gmii_top__DOT__hold_byte = 0U;
        vlTOPp->cov_tx_byte = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->gmii_top__DOT__frame_start) {
            __Vdly__cov_frame_len = 0U;
        } else {
            if (vlTOPp->gmii_top__DOT__pop_evt) {
                __Vdly__cov_frame_len = (0xffffU & 
                                         ((IData)(1U) 
                                          + (IData)(vlTOPp->cov_frame_len)));
            }
        }
        vlTOPp->cov_seq12 = 0U;
        if (vlTOPp->gmii_top__DOT__tx_done_evt) {
            if (((IData)(vlTOPp->gmii_top__DOT__len_seen) 
                 & ((IData)(vlTOPp->cov_frame_len) 
                    == (IData)(vlTOPp->gmii_top__DOT__last_len)))) {
                vlTOPp->cov_seq12 = 1U;
            }
            vlTOPp->gmii_top__DOT__last_len = vlTOPp->cov_frame_len;
        }
    } else {
        __Vdly__cov_frame_len = 0U;
        vlTOPp->cov_seq12 = 0U;
        vlTOPp->gmii_top__DOT__last_len = 0U;
    }
    if (vlTOPp->rst_n) {
        if (((IData)(vlTOPp->gmii_top__DOT__pop_evt) 
             & (IData)(vlTOPp->gmii_top__DOT__tlast_comb))) {
            vlTOPp->gmii_top__DOT__last_hold = 1U;
        } else {
            if (vlTOPp->gmii_top__DOT__hold_beat_present) {
                vlTOPp->gmii_top__DOT__last_hold = 0U;
            }
        }
    } else {
        vlTOPp->gmii_top__DOT__last_hold = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->gmii_top__DOT__cfg_ok) {
            if ((0U != (IData)(vlTOPp->cfg_sel))) {
                if ((1U == (IData)(vlTOPp->cfg_sel))) {
                    vlTOPp->gmii_top__DOT__cfg_en = 
                        (3U & (IData)(vlTOPp->cfg_data));
                }
            }
        }
    } else {
        vlTOPp->gmii_top__DOT__cfg_en = 3U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq3 = 0U;
        if (((IData)(vlTOPp->gmii_top__DOT__tx_pending) 
             & (~ (IData)(vlTOPp->tx_tready)))) {
            if ((0xfU > (IData)(vlTOPp->gmii_top__DOT__s3_cnt))) {
                __Vdly__gmii_top__DOT__s3_cnt = (0xfU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->gmii_top__DOT__s3_cnt)));
            }
            if ((1U <= (IData)(vlTOPp->gmii_top__DOT__s3_cnt))) {
                __Vdly__gmii_top__DOT__s3_armed = 1U;
            }
        } else {
            __Vdly__gmii_top__DOT__s3_cnt = 0U;
        }
        if (((IData)(vlTOPp->gmii_top__DOT__tx_done_evt) 
             & (IData)(vlTOPp->gmii_top__DOT__s3_armed))) {
            vlTOPp->cov_seq3 = 1U;
            __Vdly__gmii_top__DOT__s3_armed = 0U;
        }
    } else {
        __Vdly__gmii_top__DOT__s3_armed = 0U;
        vlTOPp->cov_seq3 = 0U;
        __Vdly__gmii_top__DOT__s3_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->gmii_top__DOT__direct_push) {
            __Vdlyvval__gmii_top__DOT__fifo__v0 = vlTOPp->tx_byte;
            __Vdlyvset__gmii_top__DOT__fifo__v0 = 1U;
            __Vdlyvdim0__gmii_top__DOT__fifo__v0 = vlTOPp->gmii_top__DOT__wr_ptr;
            __Vdly__gmii_top__DOT__wr_ptr = (0xfU & 
                                             ((IData)(1U) 
                                              + (IData)(vlTOPp->gmii_top__DOT__wr_ptr)));
        } else {
            if (vlTOPp->gmii_top__DOT__accept) {
                __Vdlyvval__gmii_top__DOT__fifo__v1 
                    = vlTOPp->gmii_top__DOT__pend_byte;
                __Vdlyvset__gmii_top__DOT__fifo__v1 = 1U;
                __Vdlyvdim0__gmii_top__DOT__fifo__v1 
                    = vlTOPp->gmii_top__DOT__wr_ptr;
                __Vdly__gmii_top__DOT__wr_ptr = (0xfU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->gmii_top__DOT__wr_ptr)));
            }
        }
    } else {
        __Vdly__gmii_top__DOT__wr_ptr = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->gmii_top__DOT__rx_tvalid_reg) {
            vlTOPp->cov_rx_byte = vlTOPp->gmii_top__DOT__rx_tdata_reg;
        }
    } else {
        vlTOPp->cov_rx_byte = 0U;
    }
    if (vlTOPp->rst_n) {
        if ((((IData)(vlTOPp->gmii_top__DOT__direct_push) 
              | (IData)(vlTOPp->gmii_top__DOT__accept)) 
             & (IData)(vlTOPp->gmii_top__DOT__pop_evt))) {
            __Vdly__gmii_top__DOT__fifo_cnt = vlTOPp->gmii_top__DOT__fifo_cnt;
        } else {
            if (((IData)(vlTOPp->gmii_top__DOT__direct_push) 
                 | (IData)(vlTOPp->gmii_top__DOT__accept))) {
                __Vdly__gmii_top__DOT__fifo_cnt = (0x1fU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)));
            } else {
                if (vlTOPp->gmii_top__DOT__pop_evt) {
                    __Vdly__gmii_top__DOT__fifo_cnt 
                        = (0x1fU & ((IData)(vlTOPp->gmii_top__DOT__fifo_cnt) 
                                    - (IData)(1U)));
                }
            }
        }
    } else {
        __Vdly__gmii_top__DOT__fifo_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq5 = 0U;
        if (vlTOPp->cov_hold) {
            if ((0xfU > (IData)(vlTOPp->gmii_top__DOT__s5_cnt))) {
                __Vdly__gmii_top__DOT__s5_cnt = (0xfU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->gmii_top__DOT__s5_cnt)));
            }
            if ((3U <= (IData)(vlTOPp->gmii_top__DOT__s5_cnt))) {
                vlTOPp->cov_seq5 = 1U;
            }
        } else {
            __Vdly__gmii_top__DOT__s5_cnt = 0U;
        }
    } else {
        __Vdly__gmii_top__DOT__s5_cnt = 0U;
        vlTOPp->cov_seq5 = 0U;
    }
    vlTOPp->gmii_top__DOT__s9_cnt = __Vdly__gmii_top__DOT__s9_cnt;
    vlTOPp->gmii_top__DOT__s7_gap = __Vdly__gmii_top__DOT__s7_gap;
    vlTOPp->gmii_top__DOT__s10_armed = __Vdly__gmii_top__DOT__s10_armed;
    vlTOPp->gmii_top__DOT__s10_cnt = __Vdly__gmii_top__DOT__s10_cnt;
    vlTOPp->gmii_top__DOT__s8_cnt = __Vdly__gmii_top__DOT__s8_cnt;
    vlTOPp->gmii_top__DOT__s1a = __Vdly__gmii_top__DOT__s1a;
    vlTOPp->gmii_top__DOT__s1b = __Vdly__gmii_top__DOT__s1b;
    vlTOPp->gmii_top__DOT__rd_ptr = __Vdly__gmii_top__DOT__rd_ptr;
    vlTOPp->cov_frame_len = __Vdly__cov_frame_len;
    vlTOPp->gmii_top__DOT__s3_cnt = __Vdly__gmii_top__DOT__s3_cnt;
    vlTOPp->gmii_top__DOT__s3_armed = __Vdly__gmii_top__DOT__s3_armed;
    vlTOPp->gmii_top__DOT__wr_ptr = __Vdly__gmii_top__DOT__wr_ptr;
    if (__Vdlyvset__gmii_top__DOT__fifo__v0) {
        vlTOPp->gmii_top__DOT__fifo[__Vdlyvdim0__gmii_top__DOT__fifo__v0] 
            = __Vdlyvval__gmii_top__DOT__fifo__v0;
    }
    if (__Vdlyvset__gmii_top__DOT__fifo__v1) {
        vlTOPp->gmii_top__DOT__fifo[__Vdlyvdim0__gmii_top__DOT__fifo__v1] 
            = __Vdlyvval__gmii_top__DOT__fifo__v1;
    }
    vlTOPp->gmii_top__DOT__fifo_cnt = __Vdly__gmii_top__DOT__fifo_cnt;
    vlTOPp->gmii_top__DOT__s5_cnt = __Vdly__gmii_top__DOT__s5_cnt;
    vlTOPp->gmii_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->gmii_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->gmii_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->gmii_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->gmii_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->gmii_top__DOT__cov_rx_err = vlTOPp->cov_rx_err;
    vlTOPp->gmii_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->gmii_top__DOT__rx_dv_prev = ((IData)(vlTOPp->rst_n) 
                                         & (IData)(vlTOPp->gmii_rx_dv));
    vlTOPp->gmii_top__DOT__u_tx__DOT__cfg_ifg = vlTOPp->gmii_top__DOT__cfg_ifg;
    vlTOPp->cov_ifg = vlTOPp->gmii_top__DOT__cfg_ifg;
    vlTOPp->gmii_top__DOT__er_d3 = ((IData)(vlTOPp->rst_n) 
                                    & (IData)(vlTOPp->gmii_top__DOT__er_d2));
    vlTOPp->gmii_top__DOT__dv_d3 = ((IData)(vlTOPp->rst_n) 
                                    & ((IData)(vlTOPp->gmii_top__DOT__dv_d2) 
                                       & (IData)(vlTOPp->gmii_rx_dv)));
    vlTOPp->gmii_top__DOT__cov_tx_byte = vlTOPp->cov_tx_byte;
    vlTOPp->gmii_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    if (vlTOPp->rst_n) {
        if (vlTOPp->gmii_top__DOT__tx_done_evt) {
            vlTOPp->gmii_top__DOT__len_seen = 1U;
        }
    } else {
        vlTOPp->gmii_top__DOT__len_seen = 0U;
    }
    vlTOPp->gmii_top__DOT__cov_frame_len = vlTOPp->cov_frame_len;
    vlTOPp->gmii_top__DOT__len8 = (0xffU & (IData)(vlTOPp->cov_frame_len));
    vlTOPp->gmii_top__DOT__hold_beat_present = vlTOPp->gmii_top__DOT__last_hold;
    vlTOPp->gmii_top__DOT__u_rx__DOT__cfg_rx_enable 
        = (1U & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                 >> 0U));
    vlTOPp->gmii_top__DOT__u_tx__DOT__cfg_tx_enable 
        = (1U & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                 >> 1U));
    vlTOPp->cov_rx_en = (1U & (IData)(vlTOPp->gmii_top__DOT__cfg_en));
    vlTOPp->gmii_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    if (vlTOPp->rst_n) {
        if (vlTOPp->gmii_top__DOT__send_ok) {
            vlTOPp->gmii_top__DOT__tx_pending = (1U 
                                                 & (~ (IData)(vlTOPp->gmii_top__DOT__direct_push)));
        } else {
            if (vlTOPp->gmii_top__DOT__accept) {
                vlTOPp->gmii_top__DOT__tx_pending = 0U;
            }
        }
    } else {
        vlTOPp->gmii_top__DOT__tx_pending = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->gmii_top__DOT__send_ok) {
            vlTOPp->gmii_top__DOT__pend_byte = vlTOPp->tx_byte;
        }
    } else {
        vlTOPp->gmii_top__DOT__pend_byte = 0U;
    }
    vlTOPp->gmii_top__DOT__cov_rx_byte = vlTOPp->cov_rx_byte;
    vlTOPp->gmii_top__DOT__rx_tdata_reg = ((IData)(vlTOPp->rst_n)
                                            ? (IData)(vlTOPp->gmii_top__DOT__rxd_d4)
                                            : 0U);
    if (vlTOPp->rst_n) {
        vlTOPp->gmii_top__DOT__rx_tvalid_reg = (1U 
                                                == (IData)(vlTOPp->cov_rx_state));
        vlTOPp->cov_seq2 = 0U;
        vlTOPp->cov_seq11 = 0U;
        if (((IData)(vlTOPp->gmii_top__DOT__send_ok) 
             & (~ ((((IData)(vlTOPp->gmii_top__DOT__s2a) 
                     | (IData)(vlTOPp->gmii_top__DOT__s2b)) 
                    | (IData)(vlTOPp->gmii_top__DOT__s2c)) 
                   | (IData)(vlTOPp->gmii_top__DOT__s2d))))) {
            __Vdly__gmii_top__DOT__s2a = 1U;
        }
        if (((0U != (IData)(vlTOPp->cov_tx_state)) 
             & (0U != (IData)(vlTOPp->cov_rx_state)))) {
            vlTOPp->cov_seq11 = 1U;
        }
        if (((IData)(vlTOPp->gmii_top__DOT__s2a) & (IData)(vlTOPp->gmii_top__DOT__frame_start))) {
            __Vdly__gmii_top__DOT__s2a = 0U;
            __Vdly__gmii_top__DOT__s2b = 1U;
        } else {
            if (((IData)(vlTOPp->gmii_top__DOT__s2b) 
                 & (IData)(vlTOPp->gmii_top__DOT__pop_evt))) {
                __Vdly__gmii_top__DOT__s2b = 0U;
                __Vdly__gmii_top__DOT__s2c = 1U;
            } else {
                if (((IData)(vlTOPp->gmii_top__DOT__s2c) 
                     & (6U == (IData)(vlTOPp->cov_tx_state)))) {
                    __Vdly__gmii_top__DOT__s2c = 0U;
                    __Vdly__gmii_top__DOT__s2d = 1U;
                } else {
                    if (((IData)(vlTOPp->gmii_top__DOT__s2d) 
                         & (IData)(vlTOPp->gmii_top__DOT__tx_done_evt))) {
                        vlTOPp->cov_seq2 = 1U;
                        __Vdly__gmii_top__DOT__s2d = 0U;
                    }
                }
            }
        }
    } else {
        vlTOPp->gmii_top__DOT__rx_tvalid_reg = 0U;
        vlTOPp->cov_seq2 = 0U;
        vlTOPp->cov_seq11 = 0U;
        __Vdly__gmii_top__DOT__s2a = 0U;
        __Vdly__gmii_top__DOT__s2b = 0U;
        __Vdly__gmii_top__DOT__s2c = 0U;
        __Vdly__gmii_top__DOT__s2d = 0U;
    }
    vlTOPp->gmii_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    if (vlTOPp->rst_n) {
        vlTOPp->cov_frame_ok_valid = 0U;
        if ((0U == (IData)(vlTOPp->gmii_top__DOT__hld_state))) {
            if (((IData)(vlTOPp->gmii_top__DOT__tx_done_evt) 
                 & (IData)(vlTOPp->gmii_top__DOT__tx_match))) {
                __Vdly__gmii_top__DOT__hld_class = vlTOPp->gmii_top__DOT__tx_class;
                __Vdly__gmii_top__DOT__hld_state = 1U;
                __Vdly__gmii_top__DOT__hld_cnt = 0x10U;
                vlTOPp->cov_hold = 1U;
            }
        } else {
            if ((1U == (IData)(vlTOPp->gmii_top__DOT__hld_state))) {
                if ((1U == (IData)(vlTOPp->gmii_top__DOT__hld_cnt))) {
                    vlTOPp->cov_frame_ok_valid = 1U;
                    vlTOPp->cov_frame_ok_class = vlTOPp->gmii_top__DOT__hld_class;
                    __Vdly__gmii_top__DOT__hld_state = 2U;
                    vlTOPp->cov_hold = 0U;
                } else {
                    __Vdly__gmii_top__DOT__hld_cnt 
                        = (0xffffU & ((IData)(vlTOPp->gmii_top__DOT__hld_cnt) 
                                      - (IData)(1U)));
                }
            } else {
                __Vdly__gmii_top__DOT__hld_state = 0U;
            }
        }
        vlTOPp->cov_seq6 = 0U;
        if (((1U == (IData)(vlTOPp->gmii_top__DOT__hld_state)) 
             & (1U == (IData)(vlTOPp->gmii_top__DOT__hld_cnt)))) {
            vlTOPp->cov_seq6 = 1U;
        }
    } else {
        __Vdly__gmii_top__DOT__hld_state = 0U;
        __Vdly__gmii_top__DOT__hld_cnt = 0U;
        __Vdly__gmii_top__DOT__hld_class = 0U;
        vlTOPp->cov_hold = 0U;
        vlTOPp->cov_frame_ok_valid = 0U;
        vlTOPp->cov_frame_ok_class = 0U;
        vlTOPp->cov_seq6 = 0U;
    }
    vlTOPp->gmii_top__DOT__cov_ifg = vlTOPp->cov_ifg;
    vlTOPp->gmii_top__DOT__m3 = (0xffU == (IData)(vlTOPp->gmii_top__DOT__len8));
    vlTOPp->gmii_top__DOT__m0 = (1U == (IData)(vlTOPp->gmii_top__DOT__len8));
    vlTOPp->gmii_top__DOT__m1 = (3U == (IData)(vlTOPp->gmii_top__DOT__len8));
    vlTOPp->gmii_top__DOT__m2 = (0xfeU == (IData)(vlTOPp->gmii_top__DOT__len8));
    vlTOPp->gmii_top__DOT__cov_rx_en = vlTOPp->cov_rx_en;
    vlTOPp->gmii_top__DOT__s2a = __Vdly__gmii_top__DOT__s2a;
    vlTOPp->gmii_top__DOT__s2b = __Vdly__gmii_top__DOT__s2b;
    vlTOPp->gmii_top__DOT__s2c = __Vdly__gmii_top__DOT__s2c;
    vlTOPp->gmii_top__DOT__s2d = __Vdly__gmii_top__DOT__s2d;
    vlTOPp->gmii_top__DOT__hld_class = __Vdly__gmii_top__DOT__hld_class;
    vlTOPp->gmii_top__DOT__hld_state = __Vdly__gmii_top__DOT__hld_state;
    vlTOPp->gmii_top__DOT__hld_cnt = __Vdly__gmii_top__DOT__hld_cnt;
    vlTOPp->gmii_top__DOT__er_d2 = ((IData)(vlTOPp->rst_n) 
                                    & (IData)(vlTOPp->gmii_top__DOT__er_d1));
    vlTOPp->gmii_top__DOT__dv_d2 = ((IData)(vlTOPp->rst_n) 
                                    & ((IData)(vlTOPp->gmii_top__DOT__dv_d1) 
                                       & (IData)(vlTOPp->gmii_rx_dv)));
    vlTOPp->gmii_top__DOT__tx_class = ((IData)(vlTOPp->gmii_top__DOT__m0)
                                        ? 0U : ((IData)(vlTOPp->gmii_top__DOT__m1)
                                                 ? 1U
                                                 : 
                                                ((IData)(vlTOPp->gmii_top__DOT__m2)
                                                  ? 2U
                                                  : 3U)));
    vlTOPp->gmii_top__DOT__tx_match = ((((IData)(vlTOPp->gmii_top__DOT__m0) 
                                         | (IData)(vlTOPp->gmii_top__DOT__m1)) 
                                        | (IData)(vlTOPp->gmii_top__DOT__m2)) 
                                       | (IData)(vlTOPp->gmii_top__DOT__m3));
    vlTOPp->cov_pending = vlTOPp->gmii_top__DOT__tx_pending;
    vlTOPp->gmii_top__DOT__rxd_d4 = ((IData)(vlTOPp->rst_n)
                                      ? (IData)(vlTOPp->gmii_top__DOT__rxd_d3)
                                      : 0U);
    vlTOPp->gmii_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->gmii_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    if (vlTOPp->rst_n) {
        vlTOPp->cov_rx_state = vlTOPp->gmii_top__DOT__rx_state_next;
        vlTOPp->cov_tx_state = vlTOPp->gmii_top__DOT__tx_state_next;
    } else {
        vlTOPp->cov_rx_state = 0U;
        vlTOPp->cov_tx_state = 0U;
    }
    vlTOPp->gmii_top__DOT__cov_frame_ok_valid = vlTOPp->cov_frame_ok_valid;
    vlTOPp->gmii_top__DOT__cov_frame_ok_class = vlTOPp->cov_frame_ok_class;
    vlTOPp->gmii_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->gmii_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->gmii_top__DOT__cov_pending = vlTOPp->cov_pending;
    vlTOPp->gmii_top__DOT__er_d1 = ((IData)(vlTOPp->rst_n) 
                                    & (IData)(vlTOPp->gmii_top__DOT__er_d0));
    vlTOPp->gmii_top__DOT__dv_d1 = ((IData)(vlTOPp->rst_n) 
                                    & ((IData)(vlTOPp->gmii_top__DOT__dv_d0) 
                                       & (IData)(vlTOPp->gmii_rx_dv)));
    vlTOPp->gmii_top__DOT__rxd_d3 = ((IData)(vlTOPp->rst_n)
                                      ? (IData)(vlTOPp->gmii_top__DOT__rxd_d2)
                                      : 0U);
    vlTOPp->gmii_top__DOT__cov_rx_state = vlTOPp->cov_rx_state;
    vlTOPp->gmii_top__DOT__cov_tx_state = vlTOPp->cov_tx_state;
    vlTOPp->gmii_top__DOT__min_cnt_next = vlTOPp->gmii_top__DOT__min_cnt;
    if ((4U & (IData)(vlTOPp->cov_tx_state))) {
        if ((1U & (~ ((IData)(vlTOPp->cov_tx_state) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->cov_tx_state)))) {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__min_cnt))) {
                    vlTOPp->gmii_top__DOT__min_cnt_next 
                        = (0xffU & ((IData)(vlTOPp->gmii_top__DOT__min_cnt) 
                                    - (IData)(1U)));
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__min_cnt))) {
                    vlTOPp->gmii_top__DOT__min_cnt_next 
                        = (0xffU & ((IData)(vlTOPp->gmii_top__DOT__min_cnt) 
                                    - (IData)(1U)));
                }
            } else {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__min_cnt))) {
                    vlTOPp->gmii_top__DOT__min_cnt_next 
                        = (0xffU & ((IData)(vlTOPp->gmii_top__DOT__min_cnt) 
                                    - (IData)(1U)));
                }
            }
        } else {
            if ((1U & (~ (IData)(vlTOPp->cov_tx_state)))) {
                vlTOPp->gmii_top__DOT__min_cnt_next = 0x3bU;
            }
        }
    }
    vlTOPp->gmii_top__DOT__fp_next = vlTOPp->gmii_top__DOT__fp;
    if ((4U & (IData)(vlTOPp->cov_tx_state))) {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (~ (IData)(vlTOPp->cov_tx_state)))) {
                if (((IData)(vlTOPp->gmii_top__DOT__fp) 
                     < (0xffU & ((IData)(vlTOPp->gmii_top__DOT__cfg_ifg) 
                                 - (IData)(1U))))) {
                    vlTOPp->gmii_top__DOT__fp_next 
                        = (0xffU & ((IData)(1U) + (IData)(vlTOPp->gmii_top__DOT__fp)));
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->gmii_top__DOT__fp_next = ((3U 
                                                   > (IData)(vlTOPp->gmii_top__DOT__fp))
                                                   ? 
                                                  (0xffU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->gmii_top__DOT__fp)))
                                                   : 0U);
            } else {
                if ((0U >= (IData)(vlTOPp->gmii_top__DOT__min_cnt))) {
                    vlTOPp->gmii_top__DOT__fp_next = 0U;
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if ((0U >= (IData)(vlTOPp->gmii_top__DOT__min_cnt))) {
                    vlTOPp->gmii_top__DOT__fp_next = 0U;
                }
            }
        } else {
            vlTOPp->gmii_top__DOT__fp_next = ((1U & (IData)(vlTOPp->cov_tx_state))
                                               ? ((7U 
                                                   == (IData)(vlTOPp->gmii_top__DOT__fp))
                                                   ? 0U
                                                   : 
                                                  (0xffU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->gmii_top__DOT__fp))))
                                               : 1U);
        }
    }
    vlTOPp->cov_busy = ((0U != (IData)(vlTOPp->cov_tx_state)) 
                        | (0U != (IData)(vlTOPp->cov_rx_state)));
    vlTOPp->gmii_top__DOT__tdata_comb = 0U;
    if (vlTOPp->gmii_top__DOT__last_hold) {
        vlTOPp->gmii_top__DOT__tdata_comb = vlTOPp->gmii_top__DOT__hold_byte;
    } else {
        if (((0U == (IData)(vlTOPp->cov_tx_state)) 
             | (1U == (IData)(vlTOPp->cov_tx_state)))) {
            if ((((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)) 
                  & (~ (IData)(vlTOPp->cov_hold))) 
                 & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                    >> 1U))) {
                vlTOPp->gmii_top__DOT__tdata_comb = 
                    vlTOPp->gmii_top__DOT__fifo[vlTOPp->gmii_top__DOT__rd_ptr];
            }
        } else {
            if ((2U == (IData)(vlTOPp->cov_tx_state))) {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt))) {
                    vlTOPp->gmii_top__DOT__tdata_comb 
                        = vlTOPp->gmii_top__DOT__fifo
                        [vlTOPp->gmii_top__DOT__rd_ptr];
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__tvalid_comb = 0U;
    if (vlTOPp->gmii_top__DOT__last_hold) {
        vlTOPp->gmii_top__DOT__tvalid_comb = 1U;
    } else {
        if (((0U == (IData)(vlTOPp->cov_tx_state)) 
             | (1U == (IData)(vlTOPp->cov_tx_state)))) {
            if ((((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)) 
                  & (~ (IData)(vlTOPp->cov_hold))) 
                 & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                    >> 1U))) {
                vlTOPp->gmii_top__DOT__tvalid_comb = 1U;
            }
        } else {
            if ((2U == (IData)(vlTOPp->cov_tx_state))) {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt))) {
                    vlTOPp->gmii_top__DOT__tvalid_comb = 1U;
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->gmii_top__DOT__idle_all = ((((~ (IData)(vlTOPp->cov_busy)) 
                                         & (~ (IData)(vlTOPp->cov_hold))) 
                                        & (~ (IData)(vlTOPp->gmii_top__DOT__tx_pending))) 
                                       & (0U == (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tdata 
        = vlTOPp->gmii_top__DOT__tdata_comb;
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next 
                    = vlTOPp->gmii_top__DOT__tdata_comb;
            } else {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                    if (vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_reg) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next 
                            = vlTOPp->gmii_top__DOT__tdata_comb;
                    }
                }
            }
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next 
                    = vlTOPp->gmii_top__DOT__tdata_comb;
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next = 0U;
                    }
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next = 0U;
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tvalid 
        = vlTOPp->gmii_top__DOT__tvalid_comb;
    vlTOPp->gmii_top__DOT__frame_start = ((0U == (IData)(vlTOPp->cov_tx_state)) 
                                          & (IData)(vlTOPp->gmii_top__DOT__tvalid_comb));
    vlTOPp->gmii_top__DOT__pop_evt = (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
                                       & (IData)(vlTOPp->gmii_top__DOT__tx_core_tready)) 
                                      & (~ (IData)(vlTOPp->gmii_top__DOT__hold_beat_present)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
             & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                >> 1U))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_reg;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 0U;
        if (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
             & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                >> 1U))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
                        } else {
                            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
             & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                >> 1U))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next = 0x55U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next = 0x55U;
            if ((6U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next = 0xd5U;
                }
            }
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                    = vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg;
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                        = vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg;
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next = 0U;
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                                    = (0xffU & (~ vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state));
                            } else {
                                if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                                    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                                        = (0xffU & 
                                           (~ (vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state 
                                               >> 8U)));
                                } else {
                                    if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                                        vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                                            = (0xffU 
                                               & (~ 
                                                  (vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state 
                                                   >> 0x10U)));
                                    } else {
                                        if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                                            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                                                = (0xffU 
                                                   & (~ 
                                                      (vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state 
                                                       >> 0x18U)));
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
    vlTOPp->cov_tvalid = vlTOPp->gmii_top__DOT__tvalid_comb;
    vlTOPp->gmii_top__DOT__er_d0 = ((IData)(vlTOPp->rst_n) 
                                    & (IData)(vlTOPp->gmii_rx_er));
    vlTOPp->gmii_top__DOT__dv_d0 = ((IData)(vlTOPp->rst_n) 
                                    & (IData)(vlTOPp->gmii_rx_dv));
    vlTOPp->gmii_top__DOT__rxd_d2 = ((IData)(vlTOPp->rst_n)
                                      ? (IData)(vlTOPp->gmii_top__DOT__rxd_d1)
                                      : 0U);
    vlTOPp->gmii_top__DOT__cov_tvalid = vlTOPp->cov_tvalid;
    if (vlTOPp->rst_n) {
        vlTOPp->gmii_top__DOT__rxd_d1 = vlTOPp->gmii_top__DOT__rxd_d0;
        vlTOPp->gmii_top__DOT__rxd_d0 = vlTOPp->gmii_rxd;
    } else {
        vlTOPp->gmii_top__DOT__rxd_d1 = 0U;
        vlTOPp->gmii_top__DOT__rxd_d0 = 0U;
    }
}

VL_INLINE_OPT void Vgmii_top::_combo__TOP__32(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_combo__TOP__32\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            if (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))) {
                vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast_next = 1U;
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__rst = (1U & (~ (IData)(vlTOPp->rst_n)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            if ((1U & (~ ((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                          & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))))) {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    if ((1U & (~ ((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d0) 
                                    | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d1)) 
                                   | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d2)) 
                                  | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d3))))) {
                        if (((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d0) 
                               << 0x18U) | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d1) 
                                             << 0x10U) 
                                            | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d2) 
                                                << 8U) 
                                               | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d3)))) 
                             != (~ vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next))) {
                            vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            if (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))) {
                vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    if (((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d0) 
                           | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d1)) 
                          | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d2)) 
                         | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d3))) {
                        vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_next = 1U;
                    } else {
                        if (((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d0) 
                               << 0x18U) | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d1) 
                                             << 0x10U) 
                                            | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d2) 
                                                << 8U) 
                                               | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d3)))) 
                             != (~ vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next))) {
                            vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            if (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))) {
                vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser_next 
                        = (((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d0) 
                              | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d1)) 
                             | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d2)) 
                            | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d3)) 
                           | ((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d0) 
                                << 0x18U) | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d1) 
                                              << 0x10U) 
                                             | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d2) 
                                                 << 8U) 
                                                | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d3)))) 
                              != (~ vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next)));
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__state_next = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__state_next 
            = (((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                  & (~ (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))) 
                 & (0xd5U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4))) 
                & (IData)(vlTOPp->gmii_top__DOT__cfg_en))
                ? 1U : 0U);
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_rx__DOT__state_next 
                = (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                    & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))
                    ? 2U : ((IData)(vlTOPp->gmii_rx_dv)
                             ? 1U : 0U));
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_rx__DOT__state_next 
                    = ((IData)(vlTOPp->gmii_rx_dv) ? 2U
                        : 0U);
            }
        }
    }
    vlTOPp->gmii_top__DOT__accept = ((((IData)(vlTOPp->gmii_top__DOT__tx_pending) 
                                       & (IData)(vlTOPp->tx_tready)) 
                                      & (~ (IData)(vlTOPp->cov_hold))) 
                                     & (0x10U > (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)));
    vlTOPp->gmii_top__DOT__send_ok = ((IData)(vlTOPp->tx_send) 
                                      & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->gmii_top__DOT__rx_state_next = vlTOPp->cov_rx_state;
    if ((0U == (IData)(vlTOPp->cov_rx_state))) {
        if (((((IData)(vlTOPp->gmii_top__DOT__dv_d4) 
               & (~ (IData)(vlTOPp->gmii_top__DOT__er_d4))) 
              & (0xd5U == (IData)(vlTOPp->gmii_top__DOT__rxd_d4))) 
             & (IData)(vlTOPp->gmii_top__DOT__cfg_en))) {
            vlTOPp->gmii_top__DOT__rx_state_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->cov_rx_state))) {
            if (((IData)(vlTOPp->gmii_top__DOT__dv_d4) 
                 & (IData)(vlTOPp->gmii_top__DOT__er_d4))) {
                vlTOPp->gmii_top__DOT__rx_state_next = 2U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    vlTOPp->gmii_top__DOT__rx_state_next = 0U;
                }
            }
        } else {
            if ((2U == (IData)(vlTOPp->cov_rx_state))) {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    vlTOPp->gmii_top__DOT__rx_state_next = 0U;
                }
            } else {
                vlTOPp->gmii_top__DOT__rx_state_next = 0U;
            }
        }
    }
    vlTOPp->gmii_top__DOT__cfg_ok = ((((((IData)(vlTOPp->cfg_wr) 
                                         & (~ (IData)(vlTOPp->tx_send))) 
                                        & (~ (IData)(vlTOPp->cov_hold))) 
                                       & (~ (IData)(vlTOPp->gmii_top__DOT__tx_pending))) 
                                      & (0U == (IData)(vlTOPp->cov_tx_state))) 
                                     & (0U == (IData)(vlTOPp->cov_rx_state)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__rst = vlTOPp->gmii_top__DOT__rst;
    vlTOPp->gmii_top__DOT__u_tx__DOT__rst = vlTOPp->gmii_top__DOT__rst;
    vlTOPp->gmii_top__DOT__direct_push = ((((IData)(vlTOPp->gmii_top__DOT__send_ok) 
                                            & (~ (IData)(vlTOPp->gmii_top__DOT__tx_pending))) 
                                           & (0x10U 
                                              > (IData)(vlTOPp->gmii_top__DOT__fifo_cnt))) 
                                          & (IData)(vlTOPp->tx_tready));
    vlTOPp->gmii_top__DOT__tlast_comb = 0U;
    if (vlTOPp->gmii_top__DOT__last_hold) {
        vlTOPp->gmii_top__DOT__tlast_comb = 1U;
    } else {
        if (((0U == (IData)(vlTOPp->cov_tx_state)) 
             | (1U == (IData)(vlTOPp->cov_tx_state)))) {
            if ((((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)) 
                  & (~ (IData)(vlTOPp->cov_hold))) 
                 & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                    >> 1U))) {
                vlTOPp->gmii_top__DOT__tlast_comb = 
                    ((1U == (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)) 
                     & (~ ((IData)(vlTOPp->gmii_top__DOT__direct_push) 
                           | (((IData)(vlTOPp->gmii_top__DOT__tx_pending) 
                               & (IData)(vlTOPp->tx_tready)) 
                              & (~ (IData)(vlTOPp->cov_hold))))));
            }
        } else {
            if ((2U == (IData)(vlTOPp->cov_tx_state))) {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt))) {
                    vlTOPp->gmii_top__DOT__tlast_comb 
                        = ((1U == (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)) 
                           & (~ ((IData)(vlTOPp->gmii_top__DOT__direct_push) 
                                 | (((IData)(vlTOPp->gmii_top__DOT__tx_pending) 
                                     & (IData)(vlTOPp->tx_tready)) 
                                    & (~ (IData)(vlTOPp->cov_hold))))));
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tlast 
        = vlTOPp->gmii_top__DOT__tlast_comb;
    vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                if ((1U & ((~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)) 
                           | (IData)(vlTOPp->gmii_top__DOT__tlast_comb)))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow_next 
                        = (1U & (~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)));
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_reg;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_next = 0U;
    } else {
        if ((1U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                if ((1U & ((~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)) 
                           | (IData)(vlTOPp->gmii_top__DOT__tlast_comb)))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_next 
                        = (1U & (~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)));
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__state_next = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
            = (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
                & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                   >> 1U)) ? 1U : 0U);
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                = ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))
                    ? 1U : ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))
                             ? 2U : 1U));
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                    = ((1U & ((~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)) 
                              | (IData)(vlTOPp->gmii_top__DOT__tlast_comb)))
                        ? 3U : 2U);
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                        = ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))
                            ? 4U : 5U);
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                            = ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))
                                ? 4U : 5U);
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                                = ((3U > (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))
                                    ? 5U : 6U);
                        } else {
                            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                                    = ((((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg) 
                                         < ((IData)(vlTOPp->gmii_top__DOT__cfg_ifg) 
                                            - (IData)(1U))) 
                                        | (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_reg))
                                        ? 6U : 0U);
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next = 0U;
    if (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
         & (IData)(vlTOPp->gmii_top__DOT__tx_core_tready))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next 
            = (1U & (~ (IData)(vlTOPp->gmii_top__DOT__tlast_comb)));
    }
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next = 1U;
            } else {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                    if (vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_reg) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next = 1U;
                    }
                }
            }
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next = 1U;
                if ((1U & ((~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)) 
                           | (IData)(vlTOPp->gmii_top__DOT__tlast_comb)))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next 
                        = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next;
                }
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next = 0U;
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next 
                            = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next;
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next 
                                = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next;
                        } else {
                            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next 
                                    = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__tx_state_next = vlTOPp->cov_tx_state;
    if ((4U & (IData)(vlTOPp->cov_tx_state))) {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->gmii_top__DOT__tx_state_next = 0U;
            } else {
                if (((IData)(vlTOPp->gmii_top__DOT__fp) 
                     >= (0xffU & ((IData)(vlTOPp->gmii_top__DOT__cfg_ifg) 
                                  - (IData)(1U))))) {
                    vlTOPp->gmii_top__DOT__tx_state_next = 0U;
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if ((3U <= (IData)(vlTOPp->gmii_top__DOT__fp))) {
                    vlTOPp->gmii_top__DOT__tx_state_next = 6U;
                }
            } else {
                vlTOPp->gmii_top__DOT__tx_state_next 
                    = ((0U < (IData)(vlTOPp->gmii_top__DOT__min_cnt))
                        ? 4U : 5U);
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->gmii_top__DOT__tx_state_next 
                    = ((0U < (IData)(vlTOPp->gmii_top__DOT__min_cnt))
                        ? 4U : 5U);
            } else {
                if ((1U & ((~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)) 
                           | (IData)(vlTOPp->gmii_top__DOT__tlast_comb)))) {
                    vlTOPp->gmii_top__DOT__tx_state_next = 3U;
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__fp))) {
                    vlTOPp->gmii_top__DOT__tx_state_next = 2U;
                }
            } else {
                if (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
                     & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                        >> 1U))) {
                    vlTOPp->gmii_top__DOT__tx_state_next = 1U;
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__tx_done_evt = ((6U == (IData)(vlTOPp->cov_tx_state)) 
                                          & (0U == (IData)(vlTOPp->gmii_top__DOT__tx_state_next)));
}

VL_INLINE_OPT void Vgmii_top::_sequent__TOP__33(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_sequent__TOP__33\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->gmii_top__DOT__rx_core_bad_frame = vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_reg;
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame 
        = vlTOPp->gmii_top__DOT__rx_core_bad_frame;
    vlTOPp->cov_bad_frame = vlTOPp->gmii_top__DOT__rx_core_bad_frame;
    vlTOPp->gmii_top__DOT__cov_bad_frame = vlTOPp->cov_bad_frame;
}

void Vgmii_top::_eval(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_eval\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__29(vlSymsp);
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__30(vlSymsp);
    }
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__31(vlSymsp);
    }
    vlTOPp->_combo__TOP__32(vlSymsp);
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__33(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

VL_INLINE_OPT QData Vgmii_top::_change_request(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_change_request\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vgmii_top::_change_request_1(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_change_request_1\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vgmii_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((gmii_rx_dv & 0xfeU))) {
        Verilated::overWidthError("gmii_rx_dv");}
    if (VL_UNLIKELY((gmii_rx_er & 0xfeU))) {
        Verilated::overWidthError("gmii_rx_er");}
    if (VL_UNLIKELY((tx_send & 0xfeU))) {
        Verilated::overWidthError("tx_send");}
    if (VL_UNLIKELY((tx_tready & 0xfeU))) {
        Verilated::overWidthError("tx_tready");}
    if (VL_UNLIKELY((cfg_wr & 0xfeU))) {
        Verilated::overWidthError("cfg_wr");}
    if (VL_UNLIKELY((cfg_sel & 0xfcU))) {
        Verilated::overWidthError("cfg_sel");}
}
#endif  // VL_DEBUG
