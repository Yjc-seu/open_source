// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vethmac_top.h for the primary calling header

#include "Vethmac_top.h"
#include "Vethmac_top__Syms.h"

//==========

void Vethmac_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vethmac_top::eval\n"); );
    Vethmac_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/ethmac_public/verilator_harness/../dut/ethmac_top.v", 63, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vethmac_top::_eval_initial_loop(Vethmac_top__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/ethmac_public/verilator_harness/../dut/ethmac_top.v", 63, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vethmac_top::_combo__TOP__2(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_combo__TOP__2\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__async_rst 
        = vlTOPp->ethmac_top__DOT__rst;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__async_rst 
        = vlTOPp->ethmac_top__DOT__rst;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_rst = vlTOPp->ethmac_top__DOT__rst;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_rst = vlTOPp->ethmac_top__DOT__rst;
    vlTOPp->ethmac_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->ethmac_top__DOT__gmii_rxd = vlTOPp->gmii_rxd;
    vlTOPp->ethmac_top__DOT__gmii_rx_dv = vlTOPp->gmii_rx_dv;
    vlTOPp->ethmac_top__DOT__gmii_rx_er = vlTOPp->gmii_rx_er;
    vlTOPp->ethmac_top__DOT__tx_send = vlTOPp->tx_send;
    vlTOPp->ethmac_top__DOT__tx_byte = vlTOPp->tx_byte;
    vlTOPp->ethmac_top__DOT__tx_tready = vlTOPp->tx_tready;
    vlTOPp->ethmac_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->ethmac_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->ethmac_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->cov_tready = vlTOPp->tx_tready;
    vlTOPp->ethmac_top__DOT__clk = vlTOPp->clk;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__rst 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_rst;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__rst 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_rst;
    vlTOPp->ethmac_top__DOT__cov_tready = vlTOPp->cov_tready;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_clk 
        = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_clk 
        = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_clk 
        = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_clk 
        = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_clk = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_clk = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__clk 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_clk;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__clk 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_clk;
}

VL_INLINE_OPT void Vethmac_top::_sequent__TOP__4(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_sequent__TOP__4\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*0:0*/ __Vdlyvset__ethmac_top__DOT__tx_fifo__DOT__mem__v0;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__tx_fifo__DOT__overflow_sync1_reg;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync1_reg;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__tx_fifo__DOT__good_frame_sync1_reg;
    CData/*0:0*/ __Vdlyvset__ethmac_top__DOT__rx_fifo__DOT__mem__v0;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__rx_fifo__DOT__overflow_sync1_reg;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync1_reg;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__rx_fifo__DOT__good_frame_sync1_reg;
    SData/*11:0*/ __Vdlyvdim0__ethmac_top__DOT__tx_fifo__DOT__mem__v0;
    SData/*8:0*/ __Vdlyvval__ethmac_top__DOT__tx_fifo__DOT__mem__v0;
    SData/*11:0*/ __Vdlyvdim0__ethmac_top__DOT__rx_fifo__DOT__mem__v0;
    SData/*8:0*/ __Vdlyvval__ethmac_top__DOT__rx_fifo__DOT__mem__v0;
    // Body
    __Vdlyvset__ethmac_top__DOT__tx_fifo__DOT__mem__v0 = 0U;
    __Vdlyvset__ethmac_top__DOT__rx_fifo__DOT__mem__v0 = 0U;
    __Vdly__ethmac_top__DOT__rx_fifo__DOT__overflow_sync1_reg 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync1_reg;
    __Vdly__ethmac_top__DOT__rx_fifo__DOT__good_frame_sync1_reg 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync1_reg;
    __Vdly__ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync1_reg 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync1_reg;
    __Vdly__ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync1_reg 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync1_reg;
    __Vdly__ethmac_top__DOT__tx_fifo__DOT__good_frame_sync1_reg 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync1_reg;
    __Vdly__ethmac_top__DOT__tx_fifo__DOT__overflow_sync1_reg 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync1_reg;
    if (vlTOPp->ethmac_top__DOT__tx_fifo__DOT__write) {
        __Vdlyvval__ethmac_top__DOT__tx_fifo__DOT__mem__v0 
            = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_write_data;
        __Vdlyvset__ethmac_top__DOT__tx_fifo__DOT__mem__v0 = 1U;
        __Vdlyvdim0__ethmac_top__DOT__tx_fifo__DOT__mem__v0 
            = (0xfffU & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_addr_reg));
    }
    if (vlTOPp->ethmac_top__DOT__rx_fifo__DOT__write) {
        __Vdlyvval__ethmac_top__DOT__rx_fifo__DOT__mem__v0 
            = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_write_data;
        __Vdlyvset__ethmac_top__DOT__rx_fifo__DOT__mem__v0 = 1U;
        __Vdlyvdim0__ethmac_top__DOT__rx_fifo__DOT__mem__v0 
            = (0xfffU & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_addr_reg));
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rst)) 
           & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_next));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rst)) 
           & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_reg 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_next;
    if (vlTOPp->ethmac_top__DOT__rx_fifo__DOT__store_output) {
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_data_reg 
            = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_reg;
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_next));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rst) ? 0U
            : (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_next));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rst)) 
           & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_next));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_next));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_next));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_reg 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_next;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_next));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rst)) 
           & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_next));
    __Vdly__ethmac_top__DOT__rx_fifo__DOT__overflow_sync1_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)) 
           & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync1_reg) 
              ^ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_reg)));
    __Vdly__ethmac_top__DOT__rx_fifo__DOT__good_frame_sync1_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)) 
           & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync1_reg) 
              ^ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_reg)));
    __Vdly__ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync1_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)) 
           & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync1_reg) 
              ^ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_reg)));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_next));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_reg 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_next;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rst)) 
           & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_next));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rst)) 
           & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_next));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rst)) 
           & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d3));
    if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)))) {
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync4_reg 
            = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync3_reg;
    }
    if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)))) {
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync4_reg 
            = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync3_reg;
    }
    if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)))) {
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync4_reg 
            = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync3_reg;
    }
    if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)))) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync4_reg 
            = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync3_reg;
    }
    if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)))) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync4_reg 
            = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync3_reg;
    }
    if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)))) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync4_reg 
            = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync3_reg;
    }
    __Vdly__ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync1_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg)) 
           & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync1_reg) 
              ^ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_reg)));
    __Vdly__ethmac_top__DOT__tx_fifo__DOT__good_frame_sync1_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg)) 
           & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync1_reg) 
              ^ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_reg)));
    __Vdly__ethmac_top__DOT__tx_fifo__DOT__overflow_sync1_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg)) 
           & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync1_reg) 
              ^ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_reg)));
    if (vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg) {
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg = 0U;
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg = 0U;
    } else {
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg 
            = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next;
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg 
            = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_next;
    }
    if (vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg = 0U;
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg = 0U;
    } else {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg 
            = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_next;
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg 
            = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_next;
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d3;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync2_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync1_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_sync2_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_sync1_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync2_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync1_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_sync2_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_sync1_reg));
    if (vlTOPp->ethmac_top__DOT__rst) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_reg = 0U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg = 0U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg = 0U;
    } else {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_reg 
            = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg 
            = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg 
            = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next;
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d3;
    if (vlTOPp->ethmac_top__DOT__rst) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state = 0xffffffffU;
    } else {
        if (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__reset_crc) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state = 0xffffffffU;
        } else {
            if (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__update_crc) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                    = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next;
            }
        }
    }
    if (vlTOPp->ethmac_top__DOT__rst) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state = 0xffffffffU;
    } else {
        if (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state = 0xffffffffU;
        } else {
            if (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__update_crc) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                    = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next;
            }
        }
    }
    if (vlTOPp->ethmac_top__DOT__tx_fifo__DOT__store_output) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_data_reg 
            = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_reg;
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_next));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_addr_reg 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_next;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_addr_reg 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_tx_er 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_tx_en 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_reg;
    vlTOPp->ethmac_top__DOT__rx_core_tdata = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_reg;
    vlTOPp->ethmac_top__DOT__rx_out_tlast = (1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_data_reg) 
                                                   >> 8U));
    if (vlTOPp->ethmac_top__DOT__rx_fifo__DOT__read) {
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_reg 
            = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem
            [(0xfffU & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_addr_reg))];
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_next = 1U;
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__update_crc = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__update_crc = 1U;
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__reset_crc = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__reset_crc = 1U;
    }
    vlTOPp->ethmac_top__DOT__rx_core_bad_fcs = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg;
    vlTOPp->ethmac_top__DOT__rx_core_tuser = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_next));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_next));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_next));
    vlTOPp->ethmac_top__DOT__rx_core_tlast = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_reg;
    vlTOPp->ethmac_top__DOT__rx_core_tvalid = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_reg;
    vlTOPp->ethmac_top__DOT__tx_core_tready = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d3 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rst)) 
           & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d2));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync3_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync2_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync3_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync2_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync3_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync2_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync3_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync2_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync3_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync2_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync3_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync2_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_next));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_next));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_next));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur 
        = (((1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg) 
                   >> 0xcU)) != (1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg) 
                                       >> 0xcU))) & 
           ((0xfffU & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg)) 
            == (0xfffU & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg))));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur 
        = (((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg) 
                   >> 0xcU)) != (1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg) 
                                       >> 0xcU))) & 
           ((0xfffU & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg)) 
            == (0xfffU & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg))));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d3 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d2;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync1_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_sync1_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync1_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_sync1_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_txd = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__update_crc = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if ((1U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__update_crc = 1U;
            } else {
                if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__update_crc = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc = 1U;
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc = 1U;
        } else {
            if ((2U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                if ((3U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    if ((4U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                        if ((5U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc = 1U;
                        } else {
                            if ((6U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d3 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d2;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_in 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_next 
                = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4;
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_in 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffffeU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (1U & (VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                  & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                  [0U])) ^ VL_REDXOR_32(
                                                        ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                         [0U])))));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffffdU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (2U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [1U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [1U]))) 
                    << 1U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffffbU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (4U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [2U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [2U]))) 
                    << 2U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffff7U & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (8U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [3U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [3U]))) 
                    << 3U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffffefU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x10U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [4U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [4U]))) 
                       << 4U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffffdfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x20U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [5U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [5U]))) 
                       << 5U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffffbfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x40U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [6U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [6U]))) 
                       << 6U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffff7fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x80U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [7U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [7U]))) 
                       << 7U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffeffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x100U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [8U])) ^ VL_REDXOR_32(
                                                             ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                              [8U]))) 
                        << 8U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffdffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x200U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [9U])) ^ VL_REDXOR_32(
                                                             ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                              [9U]))) 
                        << 9U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffbffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x400U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [0xaU])) ^ VL_REDXOR_32(
                                                               ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                                [0xaU]))) 
                        << 0xaU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffff7ffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x800U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [0xbU])) ^ VL_REDXOR_32(
                                                               ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                                [0xbU]))) 
                        << 0xbU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffefffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x1000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xcU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xcU]))) << 0xcU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffdfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x2000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xdU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xdU]))) << 0xdU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffbfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x4000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xeU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xeU]))) << 0xeU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffff7fffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x8000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xfU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xfU]))) << 0xfU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffeffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x10000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x10U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x10U]))) 
                          << 0x10U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffdffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x20000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x11U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x11U]))) 
                          << 0x11U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffbffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x40000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x12U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x12U]))) 
                          << 0x12U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfff7ffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x80000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x13U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x13U]))) 
                          << 0x13U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffefffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x100000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x14U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x14U]))) 
                           << 0x14U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffdfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x200000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x15U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x15U]))) 
                           << 0x15U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffbfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x400000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x16U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x16U]))) 
                           << 0x16U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xff7fffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x800000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x17U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x17U]))) 
                           << 0x17U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfeffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x1000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x18U])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x18U]))) 
                            << 0x18U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfdffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x2000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x19U])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x19U]))) 
                            << 0x19U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfbffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x4000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x1aU])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x1aU]))) 
                            << 0x1aU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xf7ffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x8000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x1bU])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x1bU]))) 
                            << 0x1bU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xefffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x10000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1cU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1cU]))) 
                             << 0x1cU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xdfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x20000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1dU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1dU]))) 
                             << 0x1dU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xbfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x40000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1eU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1eU]))) 
                             << 0x1eU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0x7fffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x80000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1fU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1fU]))) 
                             << 0x1fU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_in 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state;
    if (vlTOPp->ethmac_top__DOT__tx_fifo__DOT__read) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_reg 
            = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem
            [(0xfffU & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_addr_reg))];
    }
    vlTOPp->ethmac_top__DOT__tx_core_tlast = (1U & 
                                              ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_data_reg) 
                                               >> 8U));
    vlTOPp->ethmac_top__DOT__tx_core_tvalid = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_tx_er;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_tx_en;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_axis_tdata 
        = vlTOPp->ethmac_top__DOT__rx_core_tdata;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tdata 
        = vlTOPp->ethmac_top__DOT__rx_core_tdata;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tlast 
        = vlTOPp->ethmac_top__DOT__rx_out_tlast;
    if (__Vdlyvset__ethmac_top__DOT__rx_fifo__DOT__mem__v0) {
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem[__Vdlyvdim0__ethmac_top__DOT__rx_fifo__DOT__mem__v0] 
            = __Vdlyvval__ethmac_top__DOT__rx_fifo__DOT__mem__v0;
    }
    vlTOPp->cov_bad_fcs = vlTOPp->ethmac_top__DOT__rx_core_bad_fcs;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_error_bad_fcs 
        = vlTOPp->ethmac_top__DOT__rx_core_bad_fcs;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_axis_tuser 
        = vlTOPp->ethmac_top__DOT__rx_core_tuser;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tuser 
        = vlTOPp->ethmac_top__DOT__rx_core_tuser;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_axis_tlast 
        = vlTOPp->ethmac_top__DOT__rx_core_tlast;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_write_data 
        = (((IData)(vlTOPp->ethmac_top__DOT__rx_core_tlast) 
            << 8U) | (IData)(vlTOPp->ethmac_top__DOT__rx_core_tdata));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tlast 
        = vlTOPp->ethmac_top__DOT__rx_core_tlast;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__rx_core_tvalid;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__rx_core_tvalid;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tready 
        = vlTOPp->ethmac_top__DOT__tx_core_tready;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tready 
        = vlTOPp->ethmac_top__DOT__tx_core_tready;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_txd;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_out 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next;
    if (__Vdlyvset__ethmac_top__DOT__tx_fifo__DOT__mem__v0) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem[__Vdlyvdim0__ethmac_top__DOT__tx_fifo__DOT__mem__v0] 
            = __Vdlyvval__ethmac_top__DOT__tx_fifo__DOT__mem__v0;
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tlast 
        = vlTOPp->ethmac_top__DOT__tx_core_tlast;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tlast 
        = vlTOPp->ethmac_top__DOT__tx_core_tlast;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__tx_core_tvalid;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if ((1U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid)))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_next = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 1U;
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 1U;
            } else {
                if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 1U;
                } else {
                    if ((4U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_reg;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tready) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid))))) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_next 
            = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg;
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            if ((7U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_next = 1U;
            }
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_next = 1U;
                if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
                    if (vlTOPp->ethmac_top__DOT__tx_core_tlast) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_next = 0U;
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                = (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
            if ((7U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 0U;
            }
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                    = (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
                if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
                    if (vlTOPp->ethmac_top__DOT__tx_core_tlast) {
                        if ((0x3bU <= (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 0U;
                        }
                    }
                } else {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 0U;
                }
            } else {
                if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                        = (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
                    if ((0x3bU <= (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 0U;
                    }
                } else {
                    if ((4U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                            = (0xffffU & ((IData)(1U) 
                                          + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
                        if ((3U <= (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 0U;
                        }
                    } else {
                        if ((5U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                                = (0xffffU & ((IData)(1U) 
                                              + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
                        } else {
                            if ((6U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                                    = (0xffffU & ((IData)(1U) 
                                                  + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__tx_core_tvalid;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__store_output = 0U;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tready) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid))))) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__store_output = 1U;
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tdata;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_addr_reg 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next;
    vlTOPp->ethmac_top__DOT__cov_bad_fcs = vlTOPp->cov_bad_fcs;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_error_bad_fcs;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tuser;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_status_overflow 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_status_good_frame 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_status_bad_frame 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tlast;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tvalid;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tready;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d2 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rst)) 
           & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d1));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_status_good_frame 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync4_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync2_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync1_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_status_bad_frame 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync4_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync2_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync1_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_status_overflow 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync4_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync2_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync1_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_status_good_frame 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync4_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync2_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync1_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_status_bad_frame 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync4_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync2_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync1_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_status_overflow 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync4_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync2_reg 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)) 
           & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync1_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_status_bad_frame 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_status_good_frame 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_status_overflow 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d2 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d1;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_next));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_next));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_next));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg)
            ? 0U : (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_next));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d2 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d1;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_addr_reg 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tlast 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tlast;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tvalid;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync1_reg 
        = __Vdly__ethmac_top__DOT__rx_fifo__DOT__good_frame_sync1_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync1_reg 
        = __Vdly__ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync1_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync1_reg 
        = __Vdly__ethmac_top__DOT__rx_fifo__DOT__overflow_sync1_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync1_reg 
        = __Vdly__ethmac_top__DOT__tx_fifo__DOT__good_frame_sync1_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync1_reg 
        = __Vdly__ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync1_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync1_reg 
        = __Vdly__ethmac_top__DOT__tx_fifo__DOT__overflow_sync1_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d1 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rst)) 
           & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d0));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d1 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d0;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__empty = 
        ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_reg) 
         == (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_sync2_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full = (
                                                   (((1U 
                                                      & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg) 
                                                         >> 0xcU)) 
                                                     != 
                                                     (1U 
                                                      & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync2_reg) 
                                                         >> 0xcU))) 
                                                    & ((1U 
                                                        & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg) 
                                                           >> 0xbU)) 
                                                       != 
                                                       (1U 
                                                        & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync2_reg) 
                                                           >> 0xbU)))) 
                                                   & ((0x7ffU 
                                                       & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg)) 
                                                      == 
                                                      (0x7ffU 
                                                       & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync2_reg))));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__empty = 
        ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_reg) 
         == (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_sync2_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full = (
                                                   (((1U 
                                                      & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg) 
                                                         >> 0xcU)) 
                                                     != 
                                                     (1U 
                                                      & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync2_reg) 
                                                         >> 0xcU))) 
                                                    & ((1U 
                                                        & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg) 
                                                           >> 0xbU)) 
                                                       != 
                                                       (1U 
                                                        & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync2_reg) 
                                                           >> 0xbU)))) 
                                                   & ((0x7ffU 
                                                       & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg)) 
                                                      == 
                                                      (0x7ffU 
                                                       & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync2_reg))));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d1 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d0;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__read = 0U;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg))))) {
        if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__empty)))) {
            vlTOPp->ethmac_top__DOT__rx_fifo__DOT__read = 1U;
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg))))) {
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_next 
            = (1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__empty)));
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_reg;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg))))) {
        if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__empty)))) {
            vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next 
                = (0x1fffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_reg)));
            vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_next 
                = (0x1fffU & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next) 
                              ^ ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next) 
                                 >> 1U)));
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__write = 0U;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))))) {
                vlTOPp->ethmac_top__DOT__rx_fifo__DOT__write = 1U;
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_next = 0U;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))) {
                vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_next = 1U;
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_next = 0U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_next = 0U;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))) {
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_next = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_next = 0U;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))))) {
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    if (vlTOPp->ethmac_top__DOT__rx_core_tuser) {
                        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_next = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_next = 0U;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))))) {
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_core_tuser)))) {
                        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_next = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))) {
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next 
                        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg;
                }
            } else {
                vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next 
                    = (0x1fffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg)));
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    if (vlTOPp->ethmac_top__DOT__rx_core_tuser) {
                        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next 
                            = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg;
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))))) {
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_core_tuser)))) {
                        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_next 
                            = (0x1fffU & ((IData)(1U) 
                                          + (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg)));
                        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_next 
                            = (0x1fffU & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_next) 
                                          ^ ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_next) 
                                             >> 1U)));
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__read = 0U;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg))))) {
        if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__empty)))) {
            vlTOPp->ethmac_top__DOT__tx_fifo__DOT__read = 1U;
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg))))) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_next 
            = (1U & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__empty)));
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_reg;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg))))) {
        if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__empty)))) {
            vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next 
                = (0x1fffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_reg)));
            vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_next 
                = (0x1fffU & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next) 
                              ^ ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next) 
                                 >> 1U)));
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d0 
        = ((~ (IData)(vlTOPp->ethmac_top__DOT__rst)) 
           & (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d0 
        = vlTOPp->ethmac_top__DOT__gmii_rx_er_core;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d0 
        = vlTOPp->ethmac_top__DOT__gmii_rxd_core;
}

VL_INLINE_OPT void Vethmac_top::_sequent__TOP__5(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_sequent__TOP__5\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rst) | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync2_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rst) | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync2_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rst) | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync2_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rst) | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync2_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync2_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rst) | 
           ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync1_reg) 
            | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync1_reg)));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync2_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rst) | 
           ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync1_reg) 
            | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync1_reg)));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_axis_tready 
        = (1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync2_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rst) | 
           ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync1_reg) 
            | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync1_reg)));
    vlTOPp->ethmac_top__DOT__tx_fifo_in_tready = (1U 
                                                  & ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full)) 
                                                     & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg))));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync2_reg 
        = ((IData)(vlTOPp->ethmac_top__DOT__rst) | 
           ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync1_reg) 
            | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync1_reg)));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_axis_tready 
        = vlTOPp->ethmac_top__DOT__tx_fifo_in_tready;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync1_reg 
        = vlTOPp->ethmac_top__DOT__rst;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync1_reg 
        = vlTOPp->ethmac_top__DOT__rst;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync1_reg 
        = vlTOPp->ethmac_top__DOT__rst;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync1_reg 
        = vlTOPp->ethmac_top__DOT__rst;
}

VL_INLINE_OPT void Vethmac_top::_sequent__TOP__6(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_sequent__TOP__6\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*3:0*/ __Vdly__ethmac_top__DOT__s9_cnt;
    CData/*2:0*/ __Vdly__ethmac_top__DOT__s7_gap;
    CData/*3:0*/ __Vdly__ethmac_top__DOT__s3_cnt;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__s3_armed;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__s2a;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__s2b;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__s2c;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__s2d;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__s1a;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__s1b;
    CData/*4:0*/ __Vdly__ethmac_top__DOT__fifo_cnt;
    CData/*4:0*/ __Vdly__ethmac_top__DOT__s8_cnt;
    CData/*7:0*/ __Vdly__cov_fifo_level;
    CData/*3:0*/ __Vdly__ethmac_top__DOT__s5_cnt;
    CData/*3:0*/ __Vdlyvdim0__ethmac_top__DOT__fifo__v0;
    CData/*7:0*/ __Vdlyvval__ethmac_top__DOT__fifo__v0;
    CData/*0:0*/ __Vdlyvset__ethmac_top__DOT__fifo__v0;
    CData/*3:0*/ __Vdly__ethmac_top__DOT__wr_ptr;
    CData/*3:0*/ __Vdlyvdim0__ethmac_top__DOT__fifo__v1;
    CData/*7:0*/ __Vdlyvval__ethmac_top__DOT__fifo__v1;
    CData/*0:0*/ __Vdlyvset__ethmac_top__DOT__fifo__v1;
    CData/*1:0*/ __Vdly__ethmac_top__DOT__hld_class;
    CData/*1:0*/ __Vdly__ethmac_top__DOT__hld_state;
    CData/*0:0*/ __Vdly__ethmac_top__DOT__s10_armed;
    CData/*1:0*/ __Vdly__ethmac_top__DOT__s10_cnt;
    SData/*15:0*/ __Vdly__cov_frame_len;
    SData/*15:0*/ __Vdly__ethmac_top__DOT__hld_cnt;
    // Body
    __Vdly__ethmac_top__DOT__s9_cnt = vlTOPp->ethmac_top__DOT__s9_cnt;
    __Vdly__ethmac_top__DOT__s7_gap = vlTOPp->ethmac_top__DOT__s7_gap;
    __Vdly__cov_fifo_level = vlTOPp->cov_fifo_level;
    __Vdly__ethmac_top__DOT__s10_cnt = vlTOPp->ethmac_top__DOT__s10_cnt;
    __Vdly__ethmac_top__DOT__s10_armed = vlTOPp->ethmac_top__DOT__s10_armed;
    __Vdly__ethmac_top__DOT__s8_cnt = vlTOPp->ethmac_top__DOT__s8_cnt;
    __Vdly__ethmac_top__DOT__s1b = vlTOPp->ethmac_top__DOT__s1b;
    __Vdly__ethmac_top__DOT__s1a = vlTOPp->ethmac_top__DOT__s1a;
    __Vdly__cov_frame_len = vlTOPp->cov_frame_len;
    __Vdly__ethmac_top__DOT__s2d = vlTOPp->ethmac_top__DOT__s2d;
    __Vdly__ethmac_top__DOT__s2c = vlTOPp->ethmac_top__DOT__s2c;
    __Vdly__ethmac_top__DOT__s2b = vlTOPp->ethmac_top__DOT__s2b;
    __Vdly__ethmac_top__DOT__s2a = vlTOPp->ethmac_top__DOT__s2a;
    __Vdly__ethmac_top__DOT__hld_cnt = vlTOPp->ethmac_top__DOT__hld_cnt;
    __Vdly__ethmac_top__DOT__hld_state = vlTOPp->ethmac_top__DOT__hld_state;
    __Vdly__ethmac_top__DOT__hld_class = vlTOPp->ethmac_top__DOT__hld_class;
    __Vdly__ethmac_top__DOT__wr_ptr = vlTOPp->ethmac_top__DOT__wr_ptr;
    __Vdlyvset__ethmac_top__DOT__fifo__v0 = 0U;
    __Vdlyvset__ethmac_top__DOT__fifo__v1 = 0U;
    __Vdly__ethmac_top__DOT__s3_armed = vlTOPp->ethmac_top__DOT__s3_armed;
    __Vdly__ethmac_top__DOT__s3_cnt = vlTOPp->ethmac_top__DOT__s3_cnt;
    __Vdly__ethmac_top__DOT__s5_cnt = vlTOPp->ethmac_top__DOT__s5_cnt;
    __Vdly__ethmac_top__DOT__fifo_cnt = vlTOPp->ethmac_top__DOT__fifo_cnt;
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq9 = 0U;
        if (vlTOPp->ethmac_top__DOT__idle_all) {
            if ((0xfU > (IData)(vlTOPp->ethmac_top__DOT__s9_cnt))) {
                __Vdly__ethmac_top__DOT__s9_cnt = (0xfU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->ethmac_top__DOT__s9_cnt)));
            }
            if ((2U <= (IData)(vlTOPp->ethmac_top__DOT__s9_cnt))) {
                vlTOPp->cov_seq9 = 1U;
            }
        } else {
            __Vdly__ethmac_top__DOT__s9_cnt = 0U;
        }
    } else {
        __Vdly__ethmac_top__DOT__s9_cnt = 0U;
        vlTOPp->cov_seq9 = 0U;
    }
    if (vlTOPp->rst_n) {
        if ((((IData)(vlTOPp->ethmac_top__DOT__fifo_in_beat) 
              & (~ (IData)(vlTOPp->ethmac_top__DOT__fifo_out_beat))) 
             & (0xffU > (IData)(vlTOPp->cov_fifo_level)))) {
            __Vdly__cov_fifo_level = (0xffU & ((IData)(1U) 
                                               + (IData)(vlTOPp->cov_fifo_level)));
        } else {
            if ((((~ (IData)(vlTOPp->ethmac_top__DOT__fifo_in_beat)) 
                  & (IData)(vlTOPp->ethmac_top__DOT__fifo_out_beat)) 
                 & (0U < (IData)(vlTOPp->cov_fifo_level)))) {
                __Vdly__cov_fifo_level = (0xffU & ((IData)(vlTOPp->cov_fifo_level) 
                                                   - (IData)(1U)));
            }
        }
    } else {
        __Vdly__cov_fifo_level = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->ethmac_top__DOT__rx_out_tvalid) {
            vlTOPp->cov_rx_byte = vlTOPp->ethmac_top__DOT__rx_out_tdata;
        }
    } else {
        vlTOPp->cov_rx_byte = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq7 = 0U;
        if (vlTOPp->ethmac_top__DOT__tx_done_evt) {
            __Vdly__ethmac_top__DOT__s7_gap = 0U;
        } else {
            if ((7U > (IData)(vlTOPp->ethmac_top__DOT__s7_gap))) {
                __Vdly__ethmac_top__DOT__s7_gap = (7U 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->ethmac_top__DOT__s7_gap)));
            }
        }
        if (((IData)(vlTOPp->ethmac_top__DOT__frame_start) 
             & (2U >= (IData)(vlTOPp->ethmac_top__DOT__s7_gap)))) {
            vlTOPp->cov_seq7 = 1U;
        }
    } else {
        vlTOPp->cov_seq7 = 0U;
        __Vdly__ethmac_top__DOT__s7_gap = 7U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq10 = 0U;
        if (vlTOPp->ethmac_top__DOT__tx_done_evt) {
            __Vdly__ethmac_top__DOT__s10_armed = 1U;
            __Vdly__ethmac_top__DOT__s10_cnt = 0U;
        } else {
            if (vlTOPp->ethmac_top__DOT__s10_armed) {
                if (vlTOPp->ethmac_top__DOT__idle_all) {
                    if ((2U >= (IData)(vlTOPp->ethmac_top__DOT__s10_cnt))) {
                        vlTOPp->cov_seq10 = 1U;
                    }
                    __Vdly__ethmac_top__DOT__s10_armed = 0U;
                } else {
                    if ((3U > (IData)(vlTOPp->ethmac_top__DOT__s10_cnt))) {
                        __Vdly__ethmac_top__DOT__s10_cnt 
                            = (3U & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__s10_cnt)));
                    }
                    if ((2U <= (IData)(vlTOPp->ethmac_top__DOT__s10_cnt))) {
                        __Vdly__ethmac_top__DOT__s10_armed = 0U;
                    }
                }
            }
        }
    } else {
        vlTOPp->cov_seq10 = 0U;
        __Vdly__ethmac_top__DOT__s10_armed = 0U;
        __Vdly__ethmac_top__DOT__s10_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq8 = 0U;
        if (vlTOPp->cov_busy) {
            if ((0x1fU > (IData)(vlTOPp->ethmac_top__DOT__s8_cnt))) {
                __Vdly__ethmac_top__DOT__s8_cnt = (0x1fU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->ethmac_top__DOT__s8_cnt)));
            }
            if ((7U <= (IData)(vlTOPp->ethmac_top__DOT__s8_cnt))) {
                vlTOPp->cov_seq8 = 1U;
            }
        } else {
            __Vdly__ethmac_top__DOT__s8_cnt = 0U;
        }
    } else {
        __Vdly__ethmac_top__DOT__s8_cnt = 0U;
        vlTOPp->cov_seq8 = 0U;
    }
    vlTOPp->ethmac_top__DOT__fp = ((IData)(vlTOPp->rst_n)
                                    ? (IData)(vlTOPp->ethmac_top__DOT__fp_next)
                                    : 0U);
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq1 = 0U;
        if ((((IData)(vlTOPp->ethmac_top__DOT__s1b) 
              & (IData)(vlTOPp->ethmac_top__DOT__rx_dv_prev_raw)) 
             & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
            vlTOPp->cov_seq1 = 1U;
            __Vdly__ethmac_top__DOT__s1a = 0U;
            __Vdly__ethmac_top__DOT__s1b = 0U;
        } else {
            if ((((IData)(vlTOPp->ethmac_top__DOT__s1a) 
                  & (IData)(vlTOPp->gmii_rx_dv)) & 
                 (0xd5U == (IData)(vlTOPp->gmii_rxd)))) {
                __Vdly__ethmac_top__DOT__s1a = 0U;
                __Vdly__ethmac_top__DOT__s1b = 1U;
            } else {
                if (((IData)(vlTOPp->ethmac_top__DOT__rx_dv_prev_raw) 
                     & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    __Vdly__ethmac_top__DOT__s1a = 0U;
                    __Vdly__ethmac_top__DOT__s1b = 0U;
                } else {
                    if ((((IData)(vlTOPp->gmii_rx_dv) 
                          & (0x55U == (IData)(vlTOPp->gmii_rxd))) 
                         & (~ (IData)(vlTOPp->ethmac_top__DOT__s1b)))) {
                        __Vdly__ethmac_top__DOT__s1a = 1U;
                    }
                }
            }
        }
    } else {
        vlTOPp->cov_seq1 = 0U;
        __Vdly__ethmac_top__DOT__s1a = 0U;
        __Vdly__ethmac_top__DOT__s1b = 0U;
    }
    vlTOPp->ethmac_top__DOT__frame_end_d = ((IData)(vlTOPp->rst_n) 
                                            & (IData)(vlTOPp->ethmac_top__DOT__frame_end));
    if (vlTOPp->rst_n) {
        if (vlTOPp->ethmac_top__DOT__staging_pop) {
            vlTOPp->ethmac_top__DOT__rd_ptr = (0xfU 
                                               & ((IData)(1U) 
                                                  + (IData)(vlTOPp->ethmac_top__DOT__rd_ptr)));
        }
    } else {
        vlTOPp->ethmac_top__DOT__rd_ptr = 0U;
    }
    vlTOPp->cov_tvalid = ((IData)(vlTOPp->rst_n) & (IData)(vlTOPp->ethmac_top__DOT__tvalid_comb));
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq4 = 0U;
        if (((IData)(vlTOPp->ethmac_top__DOT__s4a) 
             & (IData)(vlTOPp->ethmac_top__DOT__rx_core_bad_frame))) {
            vlTOPp->cov_seq4 = 1U;
            vlTOPp->ethmac_top__DOT__s4a = 0U;
        } else {
            if (((IData)(vlTOPp->gmii_rx_dv) & (IData)(vlTOPp->gmii_rx_er))) {
                vlTOPp->ethmac_top__DOT__s4a = 1U;
            }
        }
    } else {
        vlTOPp->ethmac_top__DOT__s4a = 0U;
        vlTOPp->cov_seq4 = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->ethmac_top__DOT__cfg_ok) {
            if ((0U == (IData)(vlTOPp->cfg_sel))) {
                vlTOPp->ethmac_top__DOT__cfg_ifg = vlTOPp->cfg_data;
            }
        }
    } else {
        vlTOPp->ethmac_top__DOT__cfg_ifg = 0xcU;
    }
    vlTOPp->ethmac_top__DOT__rx_dv_prev = ((IData)(vlTOPp->rst_n) 
                                           & (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core));
    vlTOPp->ethmac_top__DOT__er_d4 = ((IData)(vlTOPp->rst_n) 
                                      & (IData)(vlTOPp->ethmac_top__DOT__er_d3));
    if (vlTOPp->rst_n) {
        vlTOPp->ethmac_top__DOT__rxd_d4 = vlTOPp->ethmac_top__DOT__rxd_d3;
        vlTOPp->ethmac_top__DOT__dv_d4 = ((IData)(vlTOPp->ethmac_top__DOT__dv_d3) 
                                          & 1U);
    } else {
        vlTOPp->ethmac_top__DOT__rxd_d4 = 0U;
        vlTOPp->ethmac_top__DOT__dv_d4 = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->ethmac_top__DOT__frame_start) {
            __Vdly__cov_frame_len = 0U;
        } else {
            if (vlTOPp->ethmac_top__DOT__core_pop) {
                __Vdly__cov_frame_len = (0xffffU & 
                                         ((IData)(1U) 
                                          + (IData)(vlTOPp->cov_frame_len)));
            }
        }
        vlTOPp->cov_seq12 = 0U;
        if (vlTOPp->ethmac_top__DOT__tx_done_evt) {
            if (((IData)(vlTOPp->ethmac_top__DOT__len_seen) 
                 & ((IData)(vlTOPp->cov_frame_len) 
                    == (IData)(vlTOPp->ethmac_top__DOT__last_len)))) {
                vlTOPp->cov_seq12 = 1U;
            }
            vlTOPp->ethmac_top__DOT__last_len = vlTOPp->cov_frame_len;
        }
    } else {
        __Vdly__cov_frame_len = 0U;
        vlTOPp->cov_seq12 = 0U;
        vlTOPp->ethmac_top__DOT__last_len = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq2 = 0U;
        vlTOPp->cov_seq11 = 0U;
        if (((IData)(vlTOPp->ethmac_top__DOT__send_ok) 
             & (~ ((((IData)(vlTOPp->ethmac_top__DOT__s2a) 
                     | (IData)(vlTOPp->ethmac_top__DOT__s2b)) 
                    | (IData)(vlTOPp->ethmac_top__DOT__s2c)) 
                   | (IData)(vlTOPp->ethmac_top__DOT__s2d))))) {
            __Vdly__ethmac_top__DOT__s2a = 1U;
        }
        if (((0U != (IData)(vlTOPp->cov_tx_state)) 
             & (0U != (IData)(vlTOPp->cov_rx_state)))) {
            vlTOPp->cov_seq11 = 1U;
        }
        if (((IData)(vlTOPp->ethmac_top__DOT__s2a) 
             & (IData)(vlTOPp->ethmac_top__DOT__frame_start))) {
            __Vdly__ethmac_top__DOT__s2a = 0U;
            __Vdly__ethmac_top__DOT__s2b = 1U;
        } else {
            if (((IData)(vlTOPp->ethmac_top__DOT__s2b) 
                 & (IData)(vlTOPp->ethmac_top__DOT__core_pop))) {
                __Vdly__ethmac_top__DOT__s2b = 0U;
                __Vdly__ethmac_top__DOT__s2c = 1U;
            } else {
                if (((IData)(vlTOPp->ethmac_top__DOT__s2c) 
                     & (6U == (IData)(vlTOPp->cov_tx_state)))) {
                    __Vdly__ethmac_top__DOT__s2c = 0U;
                    __Vdly__ethmac_top__DOT__s2d = 1U;
                } else {
                    if (((IData)(vlTOPp->ethmac_top__DOT__s2d) 
                         & (IData)(vlTOPp->ethmac_top__DOT__tx_done_evt))) {
                        vlTOPp->cov_seq2 = 1U;
                        __Vdly__ethmac_top__DOT__s2d = 0U;
                    }
                }
            }
        }
    } else {
        vlTOPp->cov_seq2 = 0U;
        vlTOPp->cov_seq11 = 0U;
        __Vdly__ethmac_top__DOT__s2a = 0U;
        __Vdly__ethmac_top__DOT__s2b = 0U;
        __Vdly__ethmac_top__DOT__s2c = 0U;
        __Vdly__ethmac_top__DOT__s2d = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->ethmac_top__DOT__cfg_ok) {
            if ((0U != (IData)(vlTOPp->cfg_sel))) {
                if ((1U == (IData)(vlTOPp->cfg_sel))) {
                    vlTOPp->ethmac_top__DOT__cfg_en 
                        = (3U & (IData)(vlTOPp->cfg_data));
                }
            }
        }
    } else {
        vlTOPp->ethmac_top__DOT__cfg_en = 3U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->ethmac_top__DOT__direct_push) {
            __Vdlyvval__ethmac_top__DOT__fifo__v0 = vlTOPp->tx_byte;
            __Vdlyvset__ethmac_top__DOT__fifo__v0 = 1U;
            __Vdlyvdim0__ethmac_top__DOT__fifo__v0 
                = vlTOPp->ethmac_top__DOT__wr_ptr;
            __Vdly__ethmac_top__DOT__wr_ptr = (0xfU 
                                               & ((IData)(1U) 
                                                  + (IData)(vlTOPp->ethmac_top__DOT__wr_ptr)));
        } else {
            if (vlTOPp->ethmac_top__DOT__accept) {
                __Vdlyvval__ethmac_top__DOT__fifo__v1 
                    = vlTOPp->ethmac_top__DOT__pend_byte;
                __Vdlyvset__ethmac_top__DOT__fifo__v1 = 1U;
                __Vdlyvdim0__ethmac_top__DOT__fifo__v1 
                    = vlTOPp->ethmac_top__DOT__wr_ptr;
                __Vdly__ethmac_top__DOT__wr_ptr = (0xfU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->ethmac_top__DOT__wr_ptr)));
            }
        }
    } else {
        __Vdly__ethmac_top__DOT__wr_ptr = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq3 = 0U;
        if (((IData)(vlTOPp->ethmac_top__DOT__tx_pending) 
             & (~ (IData)(vlTOPp->tx_tready)))) {
            if ((0xfU > (IData)(vlTOPp->ethmac_top__DOT__s3_cnt))) {
                __Vdly__ethmac_top__DOT__s3_cnt = (0xfU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->ethmac_top__DOT__s3_cnt)));
            }
            if ((1U <= (IData)(vlTOPp->ethmac_top__DOT__s3_cnt))) {
                __Vdly__ethmac_top__DOT__s3_armed = 1U;
            }
        } else {
            __Vdly__ethmac_top__DOT__s3_cnt = 0U;
        }
        if (((IData)(vlTOPp->ethmac_top__DOT__tx_done_evt) 
             & (IData)(vlTOPp->ethmac_top__DOT__s3_armed))) {
            vlTOPp->cov_seq3 = 1U;
            __Vdly__ethmac_top__DOT__s3_armed = 0U;
        }
    } else {
        __Vdly__ethmac_top__DOT__s3_armed = 0U;
        vlTOPp->cov_seq3 = 0U;
        __Vdly__ethmac_top__DOT__s3_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq5 = 0U;
        if (vlTOPp->cov_hold) {
            if ((0xfU > (IData)(vlTOPp->ethmac_top__DOT__s5_cnt))) {
                __Vdly__ethmac_top__DOT__s5_cnt = (0xfU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->ethmac_top__DOT__s5_cnt)));
            }
            if ((3U <= (IData)(vlTOPp->ethmac_top__DOT__s5_cnt))) {
                vlTOPp->cov_seq5 = 1U;
            }
        } else {
            __Vdly__ethmac_top__DOT__s5_cnt = 0U;
        }
    } else {
        __Vdly__ethmac_top__DOT__s5_cnt = 0U;
        vlTOPp->cov_seq5 = 0U;
    }
    if (vlTOPp->rst_n) {
        if ((((IData)(vlTOPp->ethmac_top__DOT__direct_push) 
              | (IData)(vlTOPp->ethmac_top__DOT__accept)) 
             & (IData)(vlTOPp->ethmac_top__DOT__staging_pop))) {
            __Vdly__ethmac_top__DOT__fifo_cnt = vlTOPp->ethmac_top__DOT__fifo_cnt;
        } else {
            if (((IData)(vlTOPp->ethmac_top__DOT__direct_push) 
                 | (IData)(vlTOPp->ethmac_top__DOT__accept))) {
                __Vdly__ethmac_top__DOT__fifo_cnt = 
                    (0x1fU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)));
            } else {
                if (vlTOPp->ethmac_top__DOT__staging_pop) {
                    __Vdly__ethmac_top__DOT__fifo_cnt 
                        = (0x1fU & ((IData)(vlTOPp->ethmac_top__DOT__fifo_cnt) 
                                    - (IData)(1U)));
                }
            }
        }
    } else {
        __Vdly__ethmac_top__DOT__fifo_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->ethmac_top__DOT__core_pop) {
            vlTOPp->cov_tx_byte = vlTOPp->ethmac_top__DOT__tx_core_tdata;
        }
    } else {
        vlTOPp->cov_tx_byte = 0U;
    }
    vlTOPp->ethmac_top__DOT__s9_cnt = __Vdly__ethmac_top__DOT__s9_cnt;
    vlTOPp->cov_fifo_level = __Vdly__cov_fifo_level;
    vlTOPp->ethmac_top__DOT__s7_gap = __Vdly__ethmac_top__DOT__s7_gap;
    vlTOPp->ethmac_top__DOT__s10_armed = __Vdly__ethmac_top__DOT__s10_armed;
    vlTOPp->ethmac_top__DOT__s10_cnt = __Vdly__ethmac_top__DOT__s10_cnt;
    vlTOPp->ethmac_top__DOT__s8_cnt = __Vdly__ethmac_top__DOT__s8_cnt;
    vlTOPp->ethmac_top__DOT__s1a = __Vdly__ethmac_top__DOT__s1a;
    vlTOPp->ethmac_top__DOT__s1b = __Vdly__ethmac_top__DOT__s1b;
    vlTOPp->cov_frame_len = __Vdly__cov_frame_len;
    vlTOPp->ethmac_top__DOT__s2a = __Vdly__ethmac_top__DOT__s2a;
    vlTOPp->ethmac_top__DOT__s2b = __Vdly__ethmac_top__DOT__s2b;
    vlTOPp->ethmac_top__DOT__s2c = __Vdly__ethmac_top__DOT__s2c;
    vlTOPp->ethmac_top__DOT__s2d = __Vdly__ethmac_top__DOT__s2d;
    vlTOPp->ethmac_top__DOT__wr_ptr = __Vdly__ethmac_top__DOT__wr_ptr;
    if (__Vdlyvset__ethmac_top__DOT__fifo__v0) {
        vlTOPp->ethmac_top__DOT__fifo[__Vdlyvdim0__ethmac_top__DOT__fifo__v0] 
            = __Vdlyvval__ethmac_top__DOT__fifo__v0;
    }
    if (__Vdlyvset__ethmac_top__DOT__fifo__v1) {
        vlTOPp->ethmac_top__DOT__fifo[__Vdlyvdim0__ethmac_top__DOT__fifo__v1] 
            = __Vdlyvval__ethmac_top__DOT__fifo__v1;
    }
    vlTOPp->ethmac_top__DOT__s3_cnt = __Vdly__ethmac_top__DOT__s3_cnt;
    vlTOPp->ethmac_top__DOT__s3_armed = __Vdly__ethmac_top__DOT__s3_armed;
    vlTOPp->ethmac_top__DOT__s5_cnt = __Vdly__ethmac_top__DOT__s5_cnt;
    vlTOPp->ethmac_top__DOT__fifo_cnt = __Vdly__ethmac_top__DOT__fifo_cnt;
    vlTOPp->ethmac_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->ethmac_top__DOT__cov_fifo_level = vlTOPp->cov_fifo_level;
    vlTOPp->ethmac_top__DOT__cov_rx_byte = vlTOPp->cov_rx_byte;
    vlTOPp->ethmac_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->ethmac_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->ethmac_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->ethmac_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->ethmac_top__DOT__rx_dv_prev_raw = ((IData)(vlTOPp->rst_n) 
                                               & (IData)(vlTOPp->gmii_rx_dv));
    vlTOPp->ethmac_top__DOT__cov_tvalid = vlTOPp->cov_tvalid;
    vlTOPp->ethmac_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->cov_ifg = vlTOPp->ethmac_top__DOT__cfg_ifg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__ifg_delay 
        = vlTOPp->ethmac_top__DOT__cfg_ifg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
            = ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid)
                ? 1U : 0U);
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                = ((7U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))
                    ? 2U : 1U);
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                    = ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid)
                        ? ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tlast)
                            ? ((0x3bU > (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))
                                ? 3U : 4U) : 2U) : 5U);
            } else {
                if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                        = ((0x3bU > (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))
                            ? 3U : 4U);
                } else {
                    if ((4U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                            = ((3U > (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))
                                ? 4U : 6U);
                    } else {
                        if ((5U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                                = ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid)
                                    ? ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tlast)
                                        ? (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg) 
                                            < ((IData)(vlTOPp->ethmac_top__DOT__cfg_ifg) 
                                               - (IData)(1U)))
                                            ? 6U : 0U)
                                        : 5U) : 5U);
                        } else {
                            if ((6U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                                    = (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg) 
                                        < ((IData)(vlTOPp->ethmac_top__DOT__cfg_ifg) 
                                           - (IData)(1U)))
                                        ? 6U : 0U);
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__er_d3 = ((IData)(vlTOPp->rst_n) 
                                      & (IData)(vlTOPp->ethmac_top__DOT__er_d2));
    if (vlTOPp->rst_n) {
        vlTOPp->ethmac_top__DOT__rxd_d3 = vlTOPp->ethmac_top__DOT__rxd_d2;
        vlTOPp->ethmac_top__DOT__dv_d3 = ((IData)(vlTOPp->ethmac_top__DOT__dv_d2) 
                                          & 1U);
    } else {
        vlTOPp->ethmac_top__DOT__rxd_d3 = 0U;
        vlTOPp->ethmac_top__DOT__dv_d3 = 0U;
    }
    vlTOPp->ethmac_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    if (vlTOPp->rst_n) {
        if (vlTOPp->ethmac_top__DOT__tx_done_evt) {
            vlTOPp->ethmac_top__DOT__len_seen = 1U;
        }
    } else {
        vlTOPp->ethmac_top__DOT__len_seen = 0U;
    }
    vlTOPp->ethmac_top__DOT__cov_frame_len = vlTOPp->cov_frame_len;
    vlTOPp->ethmac_top__DOT__len8 = (0xffU & (IData)(vlTOPp->cov_frame_len));
    vlTOPp->ethmac_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->ethmac_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    if (vlTOPp->rst_n) {
        vlTOPp->cov_rx_state = vlTOPp->ethmac_top__DOT__rx_state_next;
        vlTOPp->cov_tx_state = vlTOPp->ethmac_top__DOT__tx_state_next;
    } else {
        vlTOPp->cov_rx_state = 0U;
        vlTOPp->cov_tx_state = 0U;
    }
    vlTOPp->cov_rx_en = (1U & (IData)(vlTOPp->ethmac_top__DOT__cfg_en));
    if (vlTOPp->rst_n) {
        if (vlTOPp->ethmac_top__DOT__send_ok) {
            vlTOPp->ethmac_top__DOT__pend_byte = vlTOPp->tx_byte;
        }
    } else {
        vlTOPp->ethmac_top__DOT__pend_byte = 0U;
    }
    vlTOPp->ethmac_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    if (vlTOPp->rst_n) {
        if (vlTOPp->ethmac_top__DOT__send_ok) {
            vlTOPp->ethmac_top__DOT__tx_pending = (1U 
                                                   & (~ (IData)(vlTOPp->ethmac_top__DOT__direct_push)));
        } else {
            if (vlTOPp->ethmac_top__DOT__accept) {
                vlTOPp->ethmac_top__DOT__tx_pending = 0U;
            }
        }
    } else {
        vlTOPp->ethmac_top__DOT__tx_pending = 0U;
    }
    vlTOPp->ethmac_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    if (vlTOPp->rst_n) {
        vlTOPp->cov_frame_ok_valid = 0U;
        if ((0U == (IData)(vlTOPp->ethmac_top__DOT__hld_state))) {
            if (((IData)(vlTOPp->ethmac_top__DOT__tx_done_evt) 
                 & (IData)(vlTOPp->ethmac_top__DOT__tx_match))) {
                __Vdly__ethmac_top__DOT__hld_class 
                    = vlTOPp->ethmac_top__DOT__tx_class;
                __Vdly__ethmac_top__DOT__hld_state = 1U;
                __Vdly__ethmac_top__DOT__hld_cnt = 0x10U;
                vlTOPp->cov_hold = 1U;
            }
        } else {
            if ((1U == (IData)(vlTOPp->ethmac_top__DOT__hld_state))) {
                if ((1U == (IData)(vlTOPp->ethmac_top__DOT__hld_cnt))) {
                    vlTOPp->cov_frame_ok_valid = 1U;
                    vlTOPp->cov_frame_ok_class = vlTOPp->ethmac_top__DOT__hld_class;
                    __Vdly__ethmac_top__DOT__hld_state = 2U;
                    vlTOPp->cov_hold = 0U;
                } else {
                    __Vdly__ethmac_top__DOT__hld_cnt 
                        = (0xffffU & ((IData)(vlTOPp->ethmac_top__DOT__hld_cnt) 
                                      - (IData)(1U)));
                }
            } else {
                __Vdly__ethmac_top__DOT__hld_state = 0U;
            }
        }
        vlTOPp->cov_seq6 = 0U;
        if (((1U == (IData)(vlTOPp->ethmac_top__DOT__hld_state)) 
             & (1U == (IData)(vlTOPp->ethmac_top__DOT__hld_cnt)))) {
            vlTOPp->cov_seq6 = 1U;
        }
    } else {
        __Vdly__ethmac_top__DOT__hld_state = 0U;
        __Vdly__ethmac_top__DOT__hld_cnt = 0U;
        __Vdly__ethmac_top__DOT__hld_class = 0U;
        vlTOPp->cov_hold = 0U;
        vlTOPp->cov_frame_ok_valid = 0U;
        vlTOPp->cov_frame_ok_class = 0U;
        vlTOPp->cov_seq6 = 0U;
    }
    vlTOPp->ethmac_top__DOT__cov_tx_byte = vlTOPp->cov_tx_byte;
    vlTOPp->ethmac_top__DOT__cov_ifg = vlTOPp->cov_ifg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__ifg_delay 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__ifg_delay;
    vlTOPp->ethmac_top__DOT__m3 = (0xffU == (IData)(vlTOPp->ethmac_top__DOT__len8));
    vlTOPp->ethmac_top__DOT__m0 = (1U == (IData)(vlTOPp->ethmac_top__DOT__len8));
    vlTOPp->ethmac_top__DOT__m1 = (3U == (IData)(vlTOPp->ethmac_top__DOT__len8));
    vlTOPp->ethmac_top__DOT__m2 = (0xfeU == (IData)(vlTOPp->ethmac_top__DOT__len8));
    vlTOPp->ethmac_top__DOT__cov_rx_en = vlTOPp->cov_rx_en;
    vlTOPp->ethmac_top__DOT__hld_class = __Vdly__ethmac_top__DOT__hld_class;
    vlTOPp->ethmac_top__DOT__hld_state = __Vdly__ethmac_top__DOT__hld_state;
    vlTOPp->ethmac_top__DOT__hld_cnt = __Vdly__ethmac_top__DOT__hld_cnt;
    vlTOPp->ethmac_top__DOT__er_d2 = ((IData)(vlTOPp->rst_n) 
                                      & (IData)(vlTOPp->ethmac_top__DOT__er_d1));
    if (vlTOPp->rst_n) {
        vlTOPp->ethmac_top__DOT__rxd_d2 = vlTOPp->ethmac_top__DOT__rxd_d1;
        vlTOPp->ethmac_top__DOT__dv_d2 = ((IData)(vlTOPp->ethmac_top__DOT__dv_d1) 
                                          & 1U);
    } else {
        vlTOPp->ethmac_top__DOT__rxd_d2 = 0U;
        vlTOPp->ethmac_top__DOT__dv_d2 = 0U;
    }
    vlTOPp->ethmac_top__DOT__tx_class = ((IData)(vlTOPp->ethmac_top__DOT__m0)
                                          ? 0U : ((IData)(vlTOPp->ethmac_top__DOT__m1)
                                                   ? 1U
                                                   : 
                                                  ((IData)(vlTOPp->ethmac_top__DOT__m2)
                                                    ? 2U
                                                    : 3U)));
    vlTOPp->ethmac_top__DOT__tx_match = ((((IData)(vlTOPp->ethmac_top__DOT__m0) 
                                           | (IData)(vlTOPp->ethmac_top__DOT__m1)) 
                                          | (IData)(vlTOPp->ethmac_top__DOT__m2)) 
                                         | (IData)(vlTOPp->ethmac_top__DOT__m3));
    vlTOPp->ethmac_top__DOT__cov_rx_state = vlTOPp->cov_rx_state;
    vlTOPp->ethmac_top__DOT__cov_tx_state = vlTOPp->cov_tx_state;
    vlTOPp->ethmac_top__DOT__frame_start = ((0U == (IData)(vlTOPp->cov_tx_state)) 
                                            & (IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid));
    vlTOPp->ethmac_top__DOT__fp_next = vlTOPp->ethmac_top__DOT__fp;
    if ((4U & (IData)(vlTOPp->cov_tx_state))) {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (~ (IData)(vlTOPp->cov_tx_state)))) {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
            }
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
            } else {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
                if ((3U <= (IData)(vlTOPp->ethmac_top__DOT__fp))) {
                    vlTOPp->ethmac_top__DOT__fp_next = 0U;
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
                if ((0x3bU <= (IData)(vlTOPp->ethmac_top__DOT__fp))) {
                    vlTOPp->ethmac_top__DOT__fp_next = 0U;
                }
            } else {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
                if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
                    if (vlTOPp->ethmac_top__DOT__tx_core_tlast) {
                        if ((0x3bU <= (IData)(vlTOPp->ethmac_top__DOT__fp))) {
                            vlTOPp->ethmac_top__DOT__fp_next = 0U;
                        }
                    }
                } else {
                    vlTOPp->ethmac_top__DOT__fp_next = 0U;
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
                if ((7U == (IData)(vlTOPp->ethmac_top__DOT__fp))) {
                    vlTOPp->ethmac_top__DOT__fp_next = 0U;
                }
            } else {
                vlTOPp->ethmac_top__DOT__fp_next = 1U;
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_state_next = vlTOPp->cov_tx_state;
    if ((4U & (IData)(vlTOPp->cov_tx_state))) {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            vlTOPp->ethmac_top__DOT__tx_state_next 
                = ((1U & (IData)(vlTOPp->cov_tx_state))
                    ? 0U : (((IData)(vlTOPp->ethmac_top__DOT__fp) 
                             < (0xffffU & ((IData)(vlTOPp->ethmac_top__DOT__cfg_ifg) 
                                           - (IData)(1U))))
                             ? 6U : 0U));
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if (((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid) 
                     & (IData)(vlTOPp->ethmac_top__DOT__tx_core_tlast))) {
                    vlTOPp->ethmac_top__DOT__tx_state_next 
                        = (((IData)(vlTOPp->ethmac_top__DOT__fp) 
                            < (0xffffU & ((IData)(vlTOPp->ethmac_top__DOT__cfg_ifg) 
                                          - (IData)(1U))))
                            ? 6U : 0U);
                }
            } else {
                vlTOPp->ethmac_top__DOT__tx_state_next 
                    = ((3U > (IData)(vlTOPp->ethmac_top__DOT__fp))
                        ? 4U : 6U);
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            vlTOPp->ethmac_top__DOT__tx_state_next 
                = ((1U & (IData)(vlTOPp->cov_tx_state))
                    ? ((0x3bU > (IData)(vlTOPp->ethmac_top__DOT__fp))
                        ? 3U : 4U) : ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid)
                                       ? ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tlast)
                                           ? ((0x3bU 
                                               > (IData)(vlTOPp->ethmac_top__DOT__fp))
                                               ? 3U
                                               : 4U)
                                           : 2U) : 5U));
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if ((7U == (IData)(vlTOPp->ethmac_top__DOT__fp))) {
                    vlTOPp->ethmac_top__DOT__tx_state_next = 2U;
                }
            } else {
                if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
                    vlTOPp->ethmac_top__DOT__tx_state_next = 1U;
                }
            }
        }
    }
    vlTOPp->cov_busy = ((0U != (IData)(vlTOPp->cov_tx_state)) 
                        | (0U != (IData)(vlTOPp->cov_rx_state)));
    vlTOPp->cov_pending = vlTOPp->ethmac_top__DOT__tx_pending;
    vlTOPp->ethmac_top__DOT__cov_frame_ok_valid = vlTOPp->cov_frame_ok_valid;
    vlTOPp->ethmac_top__DOT__cov_frame_ok_class = vlTOPp->cov_frame_ok_class;
    vlTOPp->ethmac_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->ethmac_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->ethmac_top__DOT__tdata_comb = 0U;
    if ((((0U < (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)) 
          & (~ (IData)(vlTOPp->cov_hold))) & ((IData)(vlTOPp->ethmac_top__DOT__cfg_en) 
                                              >> 1U))) {
        vlTOPp->ethmac_top__DOT__tdata_comb = vlTOPp->ethmac_top__DOT__fifo
            [vlTOPp->ethmac_top__DOT__rd_ptr];
    }
    vlTOPp->ethmac_top__DOT__tvalid_comb = 0U;
    if ((((0U < (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)) 
          & (~ (IData)(vlTOPp->cov_hold))) & ((IData)(vlTOPp->ethmac_top__DOT__cfg_en) 
                                              >> 1U))) {
        vlTOPp->ethmac_top__DOT__tvalid_comb = 1U;
    }
    vlTOPp->ethmac_top__DOT__tx_done_evt = ((6U == (IData)(vlTOPp->cov_tx_state)) 
                                            & (0U == (IData)(vlTOPp->ethmac_top__DOT__tx_state_next)));
    vlTOPp->ethmac_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->ethmac_top__DOT__idle_all = ((((~ (IData)(vlTOPp->cov_busy)) 
                                           & (~ (IData)(vlTOPp->cov_hold))) 
                                          & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_pending))) 
                                         & (0U == (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)));
    vlTOPp->ethmac_top__DOT__cov_pending = vlTOPp->cov_pending;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_axis_tdata 
        = vlTOPp->ethmac_top__DOT__tdata_comb;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__tvalid_comb;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__write = 0U;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))))) {
                vlTOPp->ethmac_top__DOT__tx_fifo__DOT__write = 1U;
            }
        }
    }
    vlTOPp->ethmac_top__DOT__er_d1 = ((IData)(vlTOPp->rst_n) 
                                      & (IData)(vlTOPp->ethmac_top__DOT__er_d0));
    if (vlTOPp->rst_n) {
        vlTOPp->ethmac_top__DOT__rxd_d1 = vlTOPp->ethmac_top__DOT__rxd_d0;
        vlTOPp->ethmac_top__DOT__dv_d1 = ((IData)(vlTOPp->ethmac_top__DOT__dv_d0) 
                                          & 1U);
        vlTOPp->ethmac_top__DOT__er_d0 = ((IData)(vlTOPp->ethmac_top__DOT__gmii_rx_er_core) 
                                          & 1U);
        vlTOPp->ethmac_top__DOT__rxd_d0 = vlTOPp->ethmac_top__DOT__gmii_rxd_core;
        vlTOPp->ethmac_top__DOT__dv_d0 = ((IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core) 
                                          & 1U);
    } else {
        vlTOPp->ethmac_top__DOT__rxd_d1 = 0U;
        vlTOPp->ethmac_top__DOT__dv_d1 = 0U;
        vlTOPp->ethmac_top__DOT__er_d0 = 0U;
        vlTOPp->ethmac_top__DOT__rxd_d0 = 0U;
        vlTOPp->ethmac_top__DOT__dv_d0 = 0U;
    }
}

VL_INLINE_OPT void Vethmac_top::_combo__TOP__7(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_combo__TOP__7\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->ethmac_top__DOT__rst = (1U & (~ (IData)(vlTOPp->rst_n)));
    vlTOPp->ethmac_top__DOT__cfg_ok = ((((((IData)(vlTOPp->cfg_wr) 
                                           & (~ (IData)(vlTOPp->tx_send))) 
                                          & (~ (IData)(vlTOPp->cov_hold))) 
                                         & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_pending))) 
                                        & (0U == (IData)(vlTOPp->cov_tx_state))) 
                                       & (0U == (IData)(vlTOPp->cov_rx_state)));
    vlTOPp->ethmac_top__DOT__accept = ((((IData)(vlTOPp->ethmac_top__DOT__tx_pending) 
                                         & (IData)(vlTOPp->tx_tready)) 
                                        & (~ (IData)(vlTOPp->cov_hold))) 
                                       & (0x10U > (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)));
    vlTOPp->ethmac_top__DOT__send_ok = ((IData)(vlTOPp->tx_send) 
                                        & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->ethmac_top__DOT__gmii_rx_er_core = ((IData)(vlTOPp->ethmac_top__DOT__cfg_en) 
                                                & (IData)(vlTOPp->gmii_rx_er));
    vlTOPp->ethmac_top__DOT__gmii_rxd_core = ((1U & (IData)(vlTOPp->ethmac_top__DOT__cfg_en))
                                               ? (IData)(vlTOPp->gmii_rxd)
                                               : 0U);
    vlTOPp->ethmac_top__DOT__gmii_rx_dv_core = ((IData)(vlTOPp->ethmac_top__DOT__cfg_en) 
                                                & (IData)(vlTOPp->gmii_rx_dv));
    vlTOPp->ethmac_top__DOT__direct_push = ((((IData)(vlTOPp->ethmac_top__DOT__send_ok) 
                                              & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_pending))) 
                                             & (0x10U 
                                                > (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt))) 
                                            & (IData)(vlTOPp->tx_tready));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rx_er 
        = vlTOPp->ethmac_top__DOT__gmii_rx_er_core;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rxd = vlTOPp->ethmac_top__DOT__gmii_rxd_core;
    vlTOPp->ethmac_top__DOT__frame_end = (((1U == (IData)(vlTOPp->cov_rx_state)) 
                                           & (IData)(vlTOPp->ethmac_top__DOT__rx_dv_prev)) 
                                          & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            if (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_next = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_state_next = vlTOPp->cov_rx_state;
    if ((0U == (IData)(vlTOPp->cov_rx_state))) {
        if ((((IData)(vlTOPp->ethmac_top__DOT__dv_d4) 
              & (~ (IData)(vlTOPp->ethmac_top__DOT__er_d4))) 
             & (0xd5U == (IData)(vlTOPp->ethmac_top__DOT__rxd_d4)))) {
            vlTOPp->ethmac_top__DOT__rx_state_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->cov_rx_state))) {
            if (((IData)(vlTOPp->ethmac_top__DOT__dv_d4) 
                 & (IData)(vlTOPp->ethmac_top__DOT__er_d4))) {
                vlTOPp->ethmac_top__DOT__rx_state_next = 2U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    vlTOPp->ethmac_top__DOT__rx_state_next = 0U;
                }
            }
        } else {
            if ((2U == (IData)(vlTOPp->cov_rx_state))) {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    vlTOPp->ethmac_top__DOT__rx_state_next = 0U;
                }
            } else {
                vlTOPp->ethmac_top__DOT__rx_state_next = 0U;
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_next = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_next 
            = ((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                 & (~ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))) 
                & (0xd5U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4)))
                ? 1U : 0U);
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_next 
                = (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                    & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))
                    ? 2U : ((IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)
                             ? 1U : 0U));
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_next 
                    = ((IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)
                        ? 2U : 0U);
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rx_dv 
        = vlTOPp->ethmac_top__DOT__gmii_rx_dv_core;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            if ((1U & (~ ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                          & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))))) {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    if ((1U & (~ ((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d0) 
                                    | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d1)) 
                                   | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d2)) 
                                  | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d3))))) {
                        if (((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d0) 
                               << 0x18U) | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d1) 
                                             << 0x10U) 
                                            | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d2) 
                                                << 8U) 
                                               | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d3)))) 
                             != (~ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            if (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    if (((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d0) 
                           | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d1)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d2)) 
                         | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d3))) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_next = 1U;
                    } else {
                        if (((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d0) 
                               << 0x18U) | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d1) 
                                             << 0x10U) 
                                            | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d2) 
                                                << 8U) 
                                               | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d3)))) 
                             != (~ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            if (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_next 
                        = (((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d0) 
                              | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d1)) 
                             | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d2)) 
                            | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d3)) 
                           | ((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d0) 
                                << 0x18U) | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d1) 
                                              << 0x10U) 
                                             | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d2) 
                                                 << 8U) 
                                                | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d3)))) 
                              != (~ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next)));
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tlast_comb = 0U;
    if ((((0U < (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)) 
          & (~ (IData)(vlTOPp->cov_hold))) & ((IData)(vlTOPp->ethmac_top__DOT__cfg_en) 
                                              >> 1U))) {
        vlTOPp->ethmac_top__DOT__tlast_comb = ((1U 
                                                == (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)) 
                                               & (~ 
                                                  ((IData)(vlTOPp->ethmac_top__DOT__direct_push) 
                                                   | (IData)(vlTOPp->ethmac_top__DOT__accept))));
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rx_er;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rxd;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rx_dv;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_axis_tlast 
        = vlTOPp->ethmac_top__DOT__tlast_comb;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_write_data 
        = (((IData)(vlTOPp->ethmac_top__DOT__tlast_comb) 
            << 8U) | (IData)(vlTOPp->ethmac_top__DOT__tdata_comb));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_next = 0U;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))) {
                vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_next = 1U;
                if (vlTOPp->ethmac_top__DOT__tlast_comb) {
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_next = 0U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_next = 0U;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))) {
                if (vlTOPp->ethmac_top__DOT__tlast_comb) {
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_next = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_next = 0U;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))))) {
                if (vlTOPp->ethmac_top__DOT__tlast_comb) {
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_next = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))) {
                if (vlTOPp->ethmac_top__DOT__tlast_comb) {
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_next 
                        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg;
                }
            } else {
                vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_next 
                    = (0x1fffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg)));
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))))) {
                if (vlTOPp->ethmac_top__DOT__tlast_comb) {
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_next 
                        = (0x1fffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg)));
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_next 
                        = (0x1fffU & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_next) 
                                      ^ ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_next) 
                                         >> 1U)));
                }
            }
        }
    }
}

VL_INLINE_OPT void Vethmac_top::_sequent__TOP__8(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_sequent__TOP__8\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->ethmac_top__DOT__fifo_out_beat = ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid) 
                                              & (IData)(vlTOPp->ethmac_top__DOT__tx_core_tready));
    vlTOPp->ethmac_top__DOT__rx_out_tvalid = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_reg;
    vlTOPp->ethmac_top__DOT__rx_out_tdata = (0xffU 
                                             & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_data_reg));
    vlTOPp->ethmac_top__DOT__rx_core_bad_frame = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_reg;
    vlTOPp->ethmac_top__DOT__core_pop = ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid) 
                                         & (IData)(vlTOPp->ethmac_top__DOT__tx_core_tready));
    vlTOPp->ethmac_top__DOT__tx_core_tdata = (0xffU 
                                              & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_data_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__rx_out_tvalid;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tdata 
        = vlTOPp->ethmac_top__DOT__rx_out_tdata;
    vlTOPp->cov_bad_frame = vlTOPp->ethmac_top__DOT__rx_core_bad_frame;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_error_bad_frame 
        = vlTOPp->ethmac_top__DOT__rx_core_bad_frame;
    vlTOPp->cov_rx_err = ((IData)(vlTOPp->ethmac_top__DOT__rx_core_bad_frame) 
                          & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_core_bad_fcs)));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tdata 
        = vlTOPp->ethmac_top__DOT__tx_core_tdata;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tdata 
        = vlTOPp->ethmac_top__DOT__tx_core_tdata;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next = 0x55U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next = 0x55U;
            if ((7U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next = 0xd5U;
            }
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next 
                    = vlTOPp->ethmac_top__DOT__tx_core_tdata;
            } else {
                if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next = 0U;
                } else {
                    if ((4U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                        if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next 
                                = (0xffU & (~ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state));
                        } else {
                            if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next 
                                    = (0xffU & (~ (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                                   >> 8U)));
                            } else {
                                if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next 
                                        = (0xffU & 
                                           (~ (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                               >> 0x10U)));
                                } else {
                                    if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next 
                                            = (0xffU 
                                               & (~ 
                                                  (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
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
    vlTOPp->ethmac_top__DOT__cov_bad_frame = vlTOPp->cov_bad_frame;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_error_bad_frame;
    vlTOPp->ethmac_top__DOT__cov_rx_err = vlTOPp->cov_rx_err;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tdata 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tdata;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_in 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffffeU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (1U & (VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                  & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                  [0U])) ^ VL_REDXOR_32(
                                                        ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                         [0U])))));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffffdU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (2U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [1U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [1U]))) 
                    << 1U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffffbU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (4U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [2U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [2U]))) 
                    << 2U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffff7U & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (8U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [3U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [3U]))) 
                    << 3U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffffefU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x10U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [4U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [4U]))) 
                       << 4U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffffdfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x20U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [5U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [5U]))) 
                       << 5U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffffbfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x40U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [6U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [6U]))) 
                       << 6U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffff7fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x80U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [7U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [7U]))) 
                       << 7U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffeffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x100U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [8U])) ^ VL_REDXOR_32(
                                                             ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                              [8U]))) 
                        << 8U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffdffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x200U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [9U])) ^ VL_REDXOR_32(
                                                             ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                              [9U]))) 
                        << 9U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffbffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x400U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [0xaU])) ^ VL_REDXOR_32(
                                                               ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                                [0xaU]))) 
                        << 0xaU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffff7ffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x800U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [0xbU])) ^ VL_REDXOR_32(
                                                               ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                                [0xbU]))) 
                        << 0xbU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffefffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x1000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xcU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xcU]))) << 0xcU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffdfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x2000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xdU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xdU]))) << 0xdU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffbfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x4000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xeU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xeU]))) << 0xeU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffff7fffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x8000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xfU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xfU]))) << 0xfU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffeffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x10000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x10U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x10U]))) 
                          << 0x10U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffdffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x20000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x11U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x11U]))) 
                          << 0x11U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffbffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x40000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x12U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x12U]))) 
                          << 0x12U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfff7ffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x80000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x13U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x13U]))) 
                          << 0x13U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffefffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x100000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x14U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x14U]))) 
                           << 0x14U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffdfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x200000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x15U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x15U]))) 
                           << 0x15U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffbfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x400000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x16U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x16U]))) 
                           << 0x16U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xff7fffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x800000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x17U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x17U]))) 
                           << 0x17U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfeffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x1000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x18U])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x18U]))) 
                            << 0x18U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfdffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x2000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x19U])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x19U]))) 
                            << 0x19U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfbffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x4000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x1aU])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x1aU]))) 
                            << 0x1aU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xf7ffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x8000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x1bU])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x1bU]))) 
                            << 0x1bU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xefffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x10000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1cU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1cU]))) 
                             << 0x1cU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xdfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x20000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1dU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1dU]))) 
                             << 0x1dU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xbfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x40000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1eU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1eU]))) 
                             << 0x1eU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0x7fffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x80000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1fU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1fU]))) 
                             << 0x1fU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_out 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next;
}

VL_INLINE_OPT void Vethmac_top::_multiclk__TOP__9(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_multiclk__TOP__9\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->ethmac_top__DOT__staging_pop = ((IData)(vlTOPp->ethmac_top__DOT__tvalid_comb) 
                                            & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo_in_tready));
    vlTOPp->ethmac_top__DOT__fifo_in_beat = ((IData)(vlTOPp->ethmac_top__DOT__tvalid_comb) 
                                             & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo_in_tready));
}

VL_INLINE_OPT void Vethmac_top::_sequent__TOP__11(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_sequent__TOP__11\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->ethmac_top__DOT__fcs_ok_pulse = ((IData)(vlTOPp->ethmac_top__DOT__frame_end_d) 
                                             & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_core_bad_frame)));
    vlTOPp->cov_fcs_ok = vlTOPp->ethmac_top__DOT__fcs_ok_pulse;
    vlTOPp->ethmac_top__DOT__cov_fcs_ok = vlTOPp->cov_fcs_ok;
}

void Vethmac_top::_eval(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_eval\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((IData)(vlTOPp->__VinpClk__TOP__ethmac_top__DOT__rst) 
            & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__ethmac_top__DOT__rst))))) {
        vlTOPp->_sequent__TOP__5(vlSymsp);
    }
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__6(vlSymsp);
    }
    vlTOPp->_combo__TOP__7(vlSymsp);
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__8(vlSymsp);
    }
    if (((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
          | ((IData)(vlTOPp->__VinpClk__TOP__ethmac_top__DOT__rst) 
             & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__ethmac_top__DOT__rst)))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_multiclk__TOP__9(vlSymsp);
    }
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__11(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__ethmac_top__DOT__rst 
        = vlTOPp->__VinpClk__TOP__ethmac_top__DOT__rst;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
    vlTOPp->__VinpClk__TOP__ethmac_top__DOT__rst = vlTOPp->ethmac_top__DOT__rst;
}

VL_INLINE_OPT QData Vethmac_top::_change_request(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_change_request\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vethmac_top::_change_request_1(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_change_request_1\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    __req |= ((vlTOPp->ethmac_top__DOT__rst ^ vlTOPp->__Vchglast__TOP__ethmac_top__DOT__rst));
    VL_DEBUG_IF( if(__req && ((vlTOPp->ethmac_top__DOT__rst ^ vlTOPp->__Vchglast__TOP__ethmac_top__DOT__rst))) VL_DBG_MSGF("        CHANGE: /mnt/d/Projects/dut_test/open_source/ethmac_public/verilator_harness/../dut/ethmac_top.v:129: ethmac_top.rst\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__ethmac_top__DOT__rst = vlTOPp->ethmac_top__DOT__rst;
    return __req;
}

#ifdef VL_DEBUG
void Vethmac_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_eval_debug_assertions\n"); );
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
