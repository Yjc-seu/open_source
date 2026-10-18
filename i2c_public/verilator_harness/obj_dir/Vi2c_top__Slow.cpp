// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vi2c_top.h for the primary calling header

#include "Vi2c_top.h"
#include "Vi2c_top__Syms.h"

//==========

VL_CTOR_IMP(Vi2c_top), var_i2c_top__DOT__ADDR_OK_SET (0x80c1010U), 
  var_i2c_top__DOT__ADDR_HOLD_N (8U), var_i2c_top__DOT__CMD_IDLE (0U), 
  var_i2c_top__DOT__CMD_START (1U), var_i2c_top__DOT__CMD_WRITE (2U), 
  var_i2c_top__DOT__CMD_READ (3U), var_i2c_top__DOT__CMD_STOP (4U), 
  var_i2c_top__DOT__ST_IDLE (0U), var_i2c_top__DOT__ST_START (1U), 
  var_i2c_top__DOT__ST_ADDR (2U), var_i2c_top__DOT__ST_WRITE (3U), 
  var_i2c_top__DOT__ST_READ (4U), var_i2c_top__DOT__ST_ACK (5U), 
  var_i2c_top__DOT__ST_STOP (6U), var_i2c_top__DOT__u_master__DOT__STATE_IDLE (0U), 
  var_i2c_top__DOT__u_master__DOT__STATE_ACTIVE_WRITE (1U), 
  var_i2c_top__DOT__u_master__DOT__STATE_ACTIVE_READ (2U), 
  var_i2c_top__DOT__u_master__DOT__STATE_START_WAIT (3U), 
  var_i2c_top__DOT__u_master__DOT__STATE_START (4U), 
  var_i2c_top__DOT__u_master__DOT__STATE_ADDRESS_1 (5U), 
  var_i2c_top__DOT__u_master__DOT__STATE_ADDRESS_2 (6U), 
  var_i2c_top__DOT__u_master__DOT__STATE_WRITE_1 (7U), 
  var_i2c_top__DOT__u_master__DOT__STATE_WRITE_2 (8U), 
  var_i2c_top__DOT__u_master__DOT__STATE_WRITE_3 (9U), 
  var_i2c_top__DOT__u_master__DOT__STATE_READ (0xaU), 
  var_i2c_top__DOT__u_master__DOT__STATE_STOP (0xbU), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_IDLE (0U), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_ACTIVE (1U), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_REPEATED_START_1 (2U), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_REPEATED_START_2 (3U), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_START_1 (4U), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_START_2 (5U), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_1 (6U), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_2 (7U), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_3 (8U), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_1 (9U), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_2 (0xaU), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_3 (0xbU), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_4 (0xcU), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_STOP_1 (0xdU), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_STOP_2 (0xeU), 
  var_i2c_top__DOT__u_master__DOT__PHY_STATE_STOP_3 (0xfU) {
    Vi2c_top__Syms* __restrict vlSymsp = __VlSymsp = new Vi2c_top__Syms(this, name());
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vi2c_top::__Vconfigure(Vi2c_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vi2c_top::~Vi2c_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vi2c_top::_initial__TOP__1(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_initial__TOP__1\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_write_multiple = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tlast = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tready = 1U;
    vlTOPp->i2c_top__DOT__u_master__DOT__stop_on_idle = 0U;
    vlTOPp->i2c_top__DOT__hld_class_q = 0U;
    vlTOPp->i2c_top__DOT__bc_d_q = 0U;
    vlTOPp->i2c_top__DOT__tready_d_q = 0U;
    vlTOPp->i2c_top__DOT__busy_d_q = 0U;
    vlTOPp->i2c_top__DOT__ok_a3 = 0x40U;
    vlTOPp->i2c_top__DOT__u_master__DOT__last_scl_i_reg = 1U;
    vlTOPp->i2c_top__DOT__cov_cmd_q = 0U;
    vlTOPp->i2c_top__DOT__cov_wr_byte_q = 0U;
    vlTOPp->i2c_top__DOT__cov_rd_byte_q = 0U;
    vlTOPp->i2c_top__DOT__cov_rd_valid_q = 0U;
    vlTOPp->i2c_top__DOT__cov_wr_valid_q = 0U;
    vlTOPp->i2c_top__DOT__cov_any_acc_q = 0U;
    vlTOPp->i2c_top__DOT__cov_nack_q = 0U;
    vlTOPp->i2c_top__DOT__cov_sda_q = 0U;
    vlTOPp->i2c_top__DOT__cov_cmd_cont_q = 0U;
    vlTOPp->i2c_top__DOT__cov_cfg_ok_q = 0U;
    vlTOPp->i2c_top__DOT__cov_addr_ok_class_q = 0U;
    vlTOPp->i2c_top__DOT__ok_a0 = 0x10U;
    vlTOPp->i2c_top__DOT__ok_a1 = 0x20U;
    vlTOPp->i2c_top__DOT__ok_a2 = 0x30U;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_reg = 0U;
    vlTOPp->i2c_top__DOT__prescale_q = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__last_sda_i_reg = 1U;
    vlTOPp->i2c_top__DOT__cov_dir_q = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__busy_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__data_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_reg = 1U;
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_reg = 1U;
    vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__last_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_reg = 0U;
    vlTOPp->i2c_top__DOT__acc_d_q = 0U;
    vlTOPp->i2c_top__DOT__st_q = 0U;
    vlTOPp->i2c_top__DOT__cov_addr_ok_valid_q = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg = 1U;
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_i_reg = 1U;
    vlTOPp->i2c_top__DOT__u_master__DOT__bus_active_reg = 0U;
    vlTOPp->i2c_top__DOT__pend_data_q = 0U;
    vlTOPp->i2c_top__DOT__tx_addr_q = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__state_reg = 0U;
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg = 0U;
    vlTOPp->i2c_top__DOT__pend_code_q = 0U;
    vlTOPp->i2c_top__DOT__hld_cnt_q = 0U;
    vlTOPp->i2c_top__DOT__pend_valid_q = 0U;
    vlTOPp->i2c_top__DOT__cov_hold_q = 0U;
}

void Vi2c_top::_settle__TOP__2(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_settle__TOP__2\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus = 0U;
    vlTOPp->i2c_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->i2c_top__DOT__cmd = vlTOPp->cmd;
    vlTOPp->i2c_top__DOT__cmd_valid = vlTOPp->cmd_valid;
    vlTOPp->i2c_top__DOT__data_in = vlTOPp->data_in;
    vlTOPp->i2c_top__DOT__sda_in = vlTOPp->sda_in;
    vlTOPp->i2c_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->i2c_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->i2c_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->i2c_top__DOT__clk = vlTOPp->clk;
    vlTOPp->cov_seq1 = vlTOPp->i2c_top__DOT__cov_seq1_q;
    vlTOPp->cov_seq2 = vlTOPp->i2c_top__DOT__cov_seq2_q;
    vlTOPp->cov_seq3 = vlTOPp->i2c_top__DOT__cov_seq3_q;
    vlTOPp->cov_seq4 = vlTOPp->i2c_top__DOT__cov_seq4_q;
    vlTOPp->cov_seq6 = vlTOPp->i2c_top__DOT__cov_seq6_q;
    vlTOPp->cov_seq8 = vlTOPp->i2c_top__DOT__cov_seq8_q;
    vlTOPp->cov_seq9 = vlTOPp->i2c_top__DOT__cov_seq9_q;
    vlTOPp->cov_seq11 = vlTOPp->i2c_top__DOT__cov_seq11_q;
    vlTOPp->cov_seq12 = vlTOPp->i2c_top__DOT__cov_seq12_q;
    vlTOPp->i2c_top__DOT__rst = (1U & (~ (IData)(vlTOPp->rst_n)));
    vlTOPp->cov_seq5 = vlTOPp->i2c_top__DOT__cov_seq5_q;
    vlTOPp->cov_seq7 = vlTOPp->i2c_top__DOT__cov_seq7_q;
    vlTOPp->cov_seq10 = vlTOPp->i2c_top__DOT__cov_seq10_q;
    vlTOPp->cov_cmd = vlTOPp->i2c_top__DOT__cov_cmd_q;
    vlTOPp->cov_wr_byte = vlTOPp->i2c_top__DOT__cov_wr_byte_q;
    vlTOPp->cov_rd_byte = vlTOPp->i2c_top__DOT__cov_rd_byte_q;
    vlTOPp->cov_rd_valid = vlTOPp->i2c_top__DOT__cov_rd_valid_q;
    vlTOPp->cov_wr_valid = vlTOPp->i2c_top__DOT__cov_wr_valid_q;
    vlTOPp->cov_any_acc = vlTOPp->i2c_top__DOT__cov_any_acc_q;
    vlTOPp->cov_nack = vlTOPp->i2c_top__DOT__cov_nack_q;
    vlTOPp->cov_sda = vlTOPp->i2c_top__DOT__cov_sda_q;
    vlTOPp->cov_cmd_cont = vlTOPp->i2c_top__DOT__cov_cmd_cont_q;
    vlTOPp->cov_cfg_ok = vlTOPp->i2c_top__DOT__cov_cfg_ok_q;
    vlTOPp->cov_addr_ok_class = vlTOPp->i2c_top__DOT__cov_addr_ok_class_q;
    vlTOPp->i2c_top__DOT__m_rd_tlast = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_reg;
    vlTOPp->i2c_top__DOT__m_missed_ack = vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_reg;
    vlTOPp->i2c_top__DOT__u_master__DOT__prescale = vlTOPp->i2c_top__DOT__prescale_q;
    vlTOPp->cov_prescale = vlTOPp->i2c_top__DOT__prescale_q;
    vlTOPp->cov_dir = vlTOPp->i2c_top__DOT__cov_dir_q;
    vlTOPp->i2c_top__DOT__m_rd_tvalid = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_reg;
    vlTOPp->i2c_top__DOT__m_rd_tdata = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata_reg;
    vlTOPp->i2c_top__DOT__m_busy = vlTOPp->i2c_top__DOT__u_master__DOT__busy_reg;
    vlTOPp->i2c_top__DOT__m_scl_t = vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_reg;
    vlTOPp->i2c_top__DOT__m_scl_o = vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_reg;
    vlTOPp->i2c_top__DOT__m_sda_t = vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_reg;
    vlTOPp->i2c_top__DOT__m_sda_o = vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_reg;
    vlTOPp->i2c_top__DOT__m_bus_control = vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_reg;
    vlTOPp->i2c_top__DOT__m_data_tready = vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_reg;
    vlTOPp->i2c_top__DOT__m_cmd_ready = vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_reg;
    vlTOPp->cov_state = vlTOPp->i2c_top__DOT__st_q;
    vlTOPp->cov_addr_ok_valid = vlTOPp->i2c_top__DOT__cov_addr_ok_valid_q;
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_posedge 
        = ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg) 
           & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_scl_i_reg)));
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_negedge 
        = ((~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg)) 
           & (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_scl_i_reg));
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_posedge 
        = ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_i_reg) 
           & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_sda_i_reg)));
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_negedge 
        = ((~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_i_reg)) 
           & (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_sda_i_reg));
    vlTOPp->i2c_top__DOT__m_bus_active = vlTOPp->i2c_top__DOT__u_master__DOT__bus_active_reg;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tdata 
        = vlTOPp->i2c_top__DOT__pend_data_q;
    vlTOPp->cov_addr = vlTOPp->i2c_top__DOT__tx_addr_q;
    vlTOPp->i2c_top__DOT__addr_nonzero = (0U != (IData)(vlTOPp->i2c_top__DOT__tx_addr_q));
    vlTOPp->i2c_top__DOT__match_class = (((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                          == (IData)(vlTOPp->i2c_top__DOT__ok_a0))
                                          ? 0U : (((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                                   == (IData)(vlTOPp->i2c_top__DOT__ok_a1))
                                                   ? 1U
                                                   : 
                                                  (((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                                    == (IData)(vlTOPp->i2c_top__DOT__ok_a2))
                                                    ? 2U
                                                    : 3U)));
    vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_next = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_next 
                                            = vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_reg;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_next 
                        = vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_reg;
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_next = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if ((1U & (~ ((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                            | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                           | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                          | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                         | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                        | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                       | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                      | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))))) {
            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if ((1U & (~ ((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                            | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                           | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                          | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                         | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                        | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                       | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                      | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))))) {
            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_next = 0U;
                            if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_next = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((1U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit = 1U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit = 1U;
                }
            } else {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__m_cmd_addr = (0x7fU & ((2U 
                                                  == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))
                                                  ? (IData)(vlTOPp->i2c_top__DOT__tx_addr_q)
                                                  : (IData)(vlTOPp->i2c_top__DOT__pend_data_q)));
    vlTOPp->cov_hold = vlTOPp->i2c_top__DOT__cov_hold_q;
    vlTOPp->i2c_top__DOT__m_data_valid = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                           & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                          & (2U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__m_cmd_start = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                          & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                         & (1U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__m_cmd_stop = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                         & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                        & (4U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__m_cmd_read = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                         & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                        & (3U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__m_cmd_write = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                          & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                         & ((1U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)) 
                                            | (2U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))));
    vlTOPp->i2c_top__DOT__m_cmd_valid = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                          & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                         & ((((1U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)) 
                                              | (3U 
                                                 == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))) 
                                             | (4U 
                                                == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))) 
                                            | (2U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))));
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_next = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if (vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg) {
                vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_next 
                    = ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_reg) 
                       & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_i_reg)));
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_reg;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 1U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U >= vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 1U;
                        } else {
                            if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 1U;
                                } else {
                                    if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 0U;
                                        } else {
                                            if ((5U 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next 
                                                    = 
                                                    (6U 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 1U;
                                } else {
                                    if ((0xaU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 0U;
                                        } else {
                                            if ((0xcU 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (0xdU 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 1U;
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
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_reg;
    if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus)))) {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U >= vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                            if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            if ((5U 
                                                 == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_next = 1U;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    if ((0xaU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((0xbU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            if ((0xcU 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (0xdU 
                                                     != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    if (
                                                        (0xeU 
                                                         != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                        vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_next = 0U;
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
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_reg;
    if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus)))) {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U >= vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    if ((1U & (~ ((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                        | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                       | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                      | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                     | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                    | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                   | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_next 
                                            = vlTOPp->i2c_top__DOT__u_master__DOT__sda_i_reg;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next = 0U;
    } else {
        if (vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg) {
            vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next 
                = ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_reg) 
                   & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg)));
        } else {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U >= vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                            if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next = 1U;
                                } else {
                                    if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            if ((5U 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (6U 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next = 1U;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next = 1U;
                                } else {
                                    if ((0xaU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((0xbU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            if ((0xcU 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (0xdU 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next = 1U;
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
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__clk = vlTOPp->i2c_top__DOT__clk;
    vlTOPp->i2c_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->i2c_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->i2c_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->i2c_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->i2c_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->i2c_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->i2c_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->i2c_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->i2c_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->i2c_top__DOT__u_master__DOT__rst = vlTOPp->i2c_top__DOT__rst;
    vlTOPp->i2c_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->i2c_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->i2c_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->i2c_top__DOT__cov_cmd = vlTOPp->cov_cmd;
    vlTOPp->i2c_top__DOT__cov_wr_byte = vlTOPp->cov_wr_byte;
    vlTOPp->i2c_top__DOT__cov_rd_byte = vlTOPp->cov_rd_byte;
    vlTOPp->i2c_top__DOT__cov_rd_valid = vlTOPp->cov_rd_valid;
    vlTOPp->i2c_top__DOT__cov_wr_valid = vlTOPp->cov_wr_valid;
    vlTOPp->i2c_top__DOT__cov_any_acc = vlTOPp->cov_any_acc;
    vlTOPp->i2c_top__DOT__cov_nack = vlTOPp->cov_nack;
    vlTOPp->i2c_top__DOT__cov_sda = vlTOPp->cov_sda;
    vlTOPp->i2c_top__DOT__cov_cmd_cont = vlTOPp->cov_cmd_cont;
    vlTOPp->i2c_top__DOT__cov_cfg_ok = vlTOPp->cov_cfg_ok;
    vlTOPp->i2c_top__DOT__cov_addr_ok_class = vlTOPp->cov_addr_ok_class;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast 
        = vlTOPp->i2c_top__DOT__m_rd_tlast;
    vlTOPp->i2c_top__DOT__e_nack = vlTOPp->i2c_top__DOT__m_missed_ack;
    vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack 
        = vlTOPp->i2c_top__DOT__m_missed_ack;
    vlTOPp->i2c_top__DOT__cov_prescale = vlTOPp->cov_prescale;
    vlTOPp->i2c_top__DOT__cov_dir = vlTOPp->cov_dir;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid 
        = vlTOPp->i2c_top__DOT__m_rd_tvalid;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata 
        = vlTOPp->i2c_top__DOT__m_rd_tdata;
    vlTOPp->i2c_top__DOT__u_master__DOT__busy = vlTOPp->i2c_top__DOT__m_busy;
    vlTOPp->i2c_top__DOT__busy_rise = ((IData)(vlTOPp->i2c_top__DOT__m_busy) 
                                       & (~ (IData)(vlTOPp->i2c_top__DOT__busy_d_q)));
    vlTOPp->cov_busy = vlTOPp->i2c_top__DOT__m_busy;
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_t = vlTOPp->i2c_top__DOT__m_scl_t;
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o = vlTOPp->i2c_top__DOT__m_scl_o;
    vlTOPp->i2c_top__DOT__scl_i_w = vlTOPp->i2c_top__DOT__m_scl_o;
    vlTOPp->scl_oe = (1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_scl_o)));
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_t = vlTOPp->i2c_top__DOT__m_sda_t;
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_o = vlTOPp->i2c_top__DOT__m_sda_o;
    vlTOPp->sda_oe = (1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_sda_o)));
    vlTOPp->i2c_top__DOT__sda_i_w = ((IData)(vlTOPp->i2c_top__DOT__m_sda_o) 
                                     & (IData)(vlTOPp->sda_in));
    vlTOPp->i2c_top__DOT__u_master__DOT__bus_control 
        = vlTOPp->i2c_top__DOT__m_bus_control;
    vlTOPp->i2c_top__DOT__e_txn_end = ((IData)(vlTOPp->i2c_top__DOT__bc_d_q) 
                                       & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_control)));
    vlTOPp->cov_bus_ctrl = vlTOPp->i2c_top__DOT__m_bus_control;
    vlTOPp->i2c_top__DOT__read_cont = (((IData)(vlTOPp->i2c_top__DOT__cov_dir_q) 
                                        & ((0x7fU & (IData)(vlTOPp->i2c_top__DOT__pend_data_q)) 
                                           == (IData)(vlTOPp->i2c_top__DOT__tx_addr_q))) 
                                       & (IData)(vlTOPp->i2c_top__DOT__m_bus_control));
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready 
        = vlTOPp->i2c_top__DOT__m_data_tready;
    vlTOPp->i2c_top__DOT__tready_rise = ((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                         & (~ (IData)(vlTOPp->i2c_top__DOT__tready_d_q)));
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready 
        = vlTOPp->i2c_top__DOT__m_cmd_ready;
    vlTOPp->i2c_top__DOT__cov_state = vlTOPp->cov_state;
    vlTOPp->i2c_top__DOT__cov_addr_ok_valid = vlTOPp->cov_addr_ok_valid;
    vlTOPp->i2c_top__DOT__u_master__DOT__stop_bit = 
        ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_posedge) 
         & (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg));
    vlTOPp->i2c_top__DOT__u_master__DOT__start_bit 
        = ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_negedge) 
           & (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg));
    vlTOPp->i2c_top__DOT__u_master__DOT__bus_active 
        = vlTOPp->i2c_top__DOT__m_bus_active;
    vlTOPp->i2c_top__DOT__cov_addr = vlTOPp->cov_addr;
    vlTOPp->i2c_top__DOT__addr_match = ((IData)(vlTOPp->i2c_top__DOT__addr_nonzero) 
                                        & (((((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                              == (IData)(vlTOPp->i2c_top__DOT__ok_a0)) 
                                             | ((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                                == (IData)(vlTOPp->i2c_top__DOT__ok_a1))) 
                                            | ((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                               == (IData)(vlTOPp->i2c_top__DOT__ok_a2))) 
                                           | ((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                              == (IData)(vlTOPp->i2c_top__DOT__ok_a3))));
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_address 
        = vlTOPp->i2c_top__DOT__m_cmd_addr;
    vlTOPp->i2c_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tvalid 
        = vlTOPp->i2c_top__DOT__m_data_valid;
    vlTOPp->i2c_top__DOT__u_master__DOT__last_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__last_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((6U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                        if (((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                             & (IData)(vlTOPp->i2c_top__DOT__m_data_valid))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__last_next = 0U;
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
    vlTOPp->i2c_top__DOT__data_acc = ((IData)(vlTOPp->i2c_top__DOT__m_data_valid) 
                                      & (IData)(vlTOPp->i2c_top__DOT__m_data_tready));
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_start 
        = vlTOPp->i2c_top__DOT__m_cmd_start;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_stop 
        = vlTOPp->i2c_top__DOT__m_cmd_stop;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_read 
        = vlTOPp->i2c_top__DOT__m_cmd_read;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_write 
        = vlTOPp->i2c_top__DOT__m_cmd_write;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_valid 
        = vlTOPp->i2c_top__DOT__m_cmd_valid;
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_next = 0U;
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_next = 0U;
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_next = 0U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 1U;
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 0U;
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 1U;
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 0U;
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next 
                            = (1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_rd_tvalid)));
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 0U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_next 
                            = vlTOPp->i2c_top__DOT__m_cmd_read;
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_next 
                                = vlTOPp->i2c_top__DOT__m_cmd_read;
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_next 
                                    = vlTOPp->i2c_top__DOT__m_cmd_read;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__addr_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__addr_next 
                            = vlTOPp->i2c_top__DOT__m_cmd_addr;
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__addr_next 
                                = vlTOPp->i2c_top__DOT__m_cmd_addr;
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__addr_next 
                                    = vlTOPp->i2c_top__DOT__m_cmd_addr;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_next 
                            = vlTOPp->i2c_top__DOT__m_cmd_stop;
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_next 
                                = vlTOPp->i2c_top__DOT__m_cmd_stop;
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_next 
                                    = vlTOPp->i2c_top__DOT__m_cmd_stop;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_next = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            if ((1U & (~ (((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                           | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                              != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                          | (IData)(vlTOPp->i2c_top__DOT__m_cmd_read))))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_next = 1U;
                            }
                        }
                    }
                } else {
                    if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg)))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_next = 1U;
                                        }
                                    } else {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_next = 1U;
                                        if (((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                             & (IData)(vlTOPp->i2c_top__DOT__m_data_valid))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_next = 0U;
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
    vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_active)))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                        }
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            if ((((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                  | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                     != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                 | (IData)(vlTOPp->i2c_top__DOT__m_cmd_read))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                            }
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                if ((1U & (~ (((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                               | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                                  != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                              | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                                }
                            }
                        }
                    } else {
                        if ((3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_active)))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                            }
                        } else {
                            if ((4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                            } else {
                                if ((5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next 
                                        = (0xfU & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                                                   - (IData)(1U)));
                                } else {
                                    if ((6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                        if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                                        }
                                    } else {
                                        if (((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                             & (IData)(vlTOPp->i2c_top__DOT__m_data_valid))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next 
                    = (0xfU & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                               - (IData)(1U)));
            } else {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next 
                            = (0xfU & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                                       - (IData)(1U)));
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__state_next = 0U;
    if (((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
         & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
        vlTOPp->i2c_top__DOT__u_master__DOT__state_next 
            = vlTOPp->i2c_top__DOT__u_master__DOT__state_reg;
    } else {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            vlTOPp->i2c_top__DOT__u_master__DOT__state_next 
                = ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                    ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                        & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))
                        ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                            ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))
                            ? ((IData)(vlTOPp->i2c_top__DOT__m_bus_active)
                                ? 3U : 5U) : 0U) : 0U)
                    : ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                        ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                            & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))
                            ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))
                                ? ((((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                     | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                        != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                    | (IData)(vlTOPp->i2c_top__DOT__m_cmd_read))
                                    ? 5U : 7U) : (((IData)(vlTOPp->i2c_top__DOT__m_cmd_stop) 
                                                   & (~ 
                                                      ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                                       | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))
                                                   ? 0U
                                                   : 1U))
                            : 1U) : ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                                      ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                                          & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))
                                          ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                              ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))
                                              ? ((((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                                   | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                                      != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                                  | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))
                                                  ? 4U
                                                  : 0xaU)
                                              : (((IData)(vlTOPp->i2c_top__DOT__m_cmd_stop) 
                                                  & (~ 
                                                     ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                                      | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))
                                                  ? 0xbU
                                                  : 2U))
                                          : 2U) : (
                                                   (3U 
                                                    == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                                                    ? 
                                                   ((IData)(vlTOPp->i2c_top__DOT__m_bus_active)
                                                     ? 3U
                                                     : 5U)
                                                    : 
                                                   ((4U 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                                                     ? 5U
                                                     : 
                                                    ((5U 
                                                      == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                                                      ? 
                                                     ((1U 
                                                       < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))
                                                       ? 5U
                                                       : 
                                                      ((0U 
                                                        < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))
                                                        ? 5U
                                                        : 6U))
                                                      : 
                                                     ((6U 
                                                       == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                                                       ? 
                                                      ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg)
                                                        ? 0xaU
                                                        : 7U)
                                                       : 
                                                      (((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                                        & (IData)(vlTOPp->i2c_top__DOT__m_data_valid))
                                                        ? 8U
                                                        : 7U))))))));
        } else {
            if ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                vlTOPp->i2c_top__DOT__u_master__DOT__state_next 
                    = ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))
                        ? 8U : 9U);
            } else {
                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__state_next 
                        = (((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_reg) 
                            & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_reg)))
                            ? 7U : ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg)
                                     ? 0U : 1U));
                } else {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__state_next 
                            = ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))
                                ? 0xaU : ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg)
                                           ? 0xbU : 2U));
                    } else {
                        if ((0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__state_next = 0U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__data_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__data_reg;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                if ((1U & (~ (((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                               | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                                  != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                              | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__data_next = 0U;
                                }
                            }
                        }
                    } else {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                        if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__data_next = 0U;
                                        }
                                    } else {
                                        if (((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                             & (IData)(vlTOPp->i2c_top__DOT__m_data_valid))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__data_next 
                                                = vlTOPp->i2c_top__DOT__pend_data_q;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__data_next 
                            = ((0xfeU & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__data_reg) 
                                         << 1U)) | (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_reg));
                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata_next 
                                = vlTOPp->i2c_top__DOT__u_master__DOT__data_next;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data 
                                    = (((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                        | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                           != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                       | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write));
                            } else {
                                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_stop) 
                                     & (~ ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                           | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data = 1U;
                                }
                            }
                        }
                    } else {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((1U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data 
                                            = ((6U 
                                                >= 
                                                (7U 
                                                 & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                                                    - (IData)(2U)))) 
                                               & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg) 
                                                  >> 
                                                  (7U 
                                                   & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                                                      - (IData)(2U)))));
                                    } else {
                                        if ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data 
                                                = vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data 
                        = (1U & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__data_reg) 
                                 >> (7U & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                                           - (IData)(1U)))));
                }
            } else {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                            } else {
                                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_stop) 
                                     & (~ ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                           | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                                }
                            }
                        }
                    } else {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((1U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                                    } else {
                                        if ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                }
            } else {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_active)))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit = 1U;
                        }
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            if ((((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                  | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                     != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                 | (IData)(vlTOPp->i2c_top__DOT__m_cmd_read))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit = 1U;
                            }
                        }
                    }
                } else {
                    if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_active)))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit = 1U;
                            }
                        } else {
                            if ((4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if ((1U & (~ ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                      ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_stop) 
                                 & (~ ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                       | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit = 1U;
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((1U & (~ ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_reg) 
                                  & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_reg)))))) {
                        if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit = 1U;
                        }
                    }
                } else {
                    if ((0xaU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__cmd_acc = ((IData)(vlTOPp->i2c_top__DOT__m_cmd_valid) 
                                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_ready));
    vlTOPp->i2c_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_i = vlTOPp->i2c_top__DOT__scl_i_w;
    vlTOPp->i2c_top__DOT__scl_oe = vlTOPp->scl_oe;
    vlTOPp->i2c_top__DOT__sda_oe = vlTOPp->sda_oe;
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_i = vlTOPp->i2c_top__DOT__sda_i_w;
    vlTOPp->i2c_top__DOT__cov_bus_ctrl = vlTOPp->cov_bus_ctrl;
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next = 0U;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next = 0U;
    } else {
        if (vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg) {
            vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next 
                = vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg;
        } else {
            if (vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg) {
                vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next 
                    = vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg;
            } else {
                if ((0U < vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next 
                        = vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg;
                } else {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next 
                            = ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                ? ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit)
                                    ? 4U : 0U) : ((1U 
                                                   == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                   ? 
                                                  ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit)
                                                    ? 2U
                                                    : 
                                                   ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit)
                                                     ? 6U
                                                     : 
                                                    ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit)
                                                      ? 9U
                                                      : 
                                                     ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit)
                                                       ? 0xdU
                                                       : 1U))))
                                                   : 
                                                  ((2U 
                                                    == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                    ? 3U
                                                    : 
                                                   ((3U 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                     ? 4U
                                                     : 
                                                    ((4U 
                                                      == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                      ? 5U
                                                      : 
                                                     ((5U 
                                                       == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                       ? 1U
                                                       : 
                                                      ((6U 
                                                        == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                        ? 7U
                                                        : 8U)))))));
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next 
                                = ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                    ? 1U : ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                             ? 0xaU
                                             : ((0xaU 
                                                 == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                 ? 0xbU
                                                 : 
                                                ((0xbU 
                                                  == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                  ? 0xcU
                                                  : 
                                                 ((0xcU 
                                                   == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                   ? 1U
                                                   : 
                                                  ((0xdU 
                                                    == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                    ? 0xeU
                                                    : 
                                                   ((0xeU 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                     ? 0xfU
                                                     : 0U)))))));
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__delay_next = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U < vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                        = (0x1ffffU & (vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg 
                                       - (IData)(1U)));
                } else {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                            if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                    = vlTOPp->i2c_top__DOT__prescale_q;
                            }
                        } else {
                            if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                        = vlTOPp->i2c_top__DOT__prescale_q;
                                } else {
                                    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                            = vlTOPp->i2c_top__DOT__prescale_q;
                                    } else {
                                        if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                = vlTOPp->i2c_top__DOT__prescale_q;
                                        } else {
                                            if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit) {
                                                vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                    = vlTOPp->i2c_top__DOT__prescale_q;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                        = vlTOPp->i2c_top__DOT__prescale_q;
                                } else {
                                    if ((3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                            = vlTOPp->i2c_top__DOT__prescale_q;
                                    } else {
                                        if ((4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                = vlTOPp->i2c_top__DOT__prescale_q;
                                        } else {
                                            if ((5U 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                    = 
                                                    (0x1ffffU 
                                                     & ((6U 
                                                         == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                         ? 
                                                        ((IData)(vlTOPp->i2c_top__DOT__prescale_q) 
                                                         << 1U)
                                                         : (IData)(vlTOPp->i2c_top__DOT__prescale_q)));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                        = vlTOPp->i2c_top__DOT__prescale_q;
                                } else {
                                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                            = vlTOPp->i2c_top__DOT__prescale_q;
                                    } else {
                                        if ((0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                = vlTOPp->i2c_top__DOT__prescale_q;
                                        } else {
                                            if ((0xcU 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (0xdU 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                        = vlTOPp->i2c_top__DOT__prescale_q;
                                                } else {
                                                    if (
                                                        (0xeU 
                                                         == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                        vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                            = vlTOPp->i2c_top__DOT__prescale_q;
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
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_reg;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 1U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U >= vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 1U;
                            if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 0U;
                            }
                        } else {
                            if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 1U;
                                } else {
                                    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next 
                                            = vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data;
                                    } else {
                                        if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 1U;
                                        } else {
                                            if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit) {
                                                vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 0U;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    if ((3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 0U;
                                    }
                                }
                            }
                        }
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    if ((0xaU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((0xbU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            if ((0xcU 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (0xdU 
                                                     != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    if (
                                                        (0xeU 
                                                         == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                        vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 1U;
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
            }
        }
    }
    vlTOPp->i2c_top__DOT__any_acc = ((IData)(vlTOPp->i2c_top__DOT__cmd_acc) 
                                     | (IData)(vlTOPp->i2c_top__DOT__data_acc));
    vlTOPp->i2c_top__DOT__pend_clear_w = ((2U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))
                                           ? (IData)(vlTOPp->i2c_top__DOT__data_acc)
                                           : (IData)(vlTOPp->i2c_top__DOT__cmd_acc));
    vlTOPp->i2c_top__DOT__acc_stop = ((((IData)(vlTOPp->i2c_top__DOT__cmd_acc) 
                                        & (4U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))) 
                                       & (IData)(vlTOPp->i2c_top__DOT__m_bus_control)) 
                                      & (~ (IData)(vlTOPp->i2c_top__DOT__m_busy)));
    vlTOPp->i2c_top__DOT__acc_start = ((IData)(vlTOPp->i2c_top__DOT__cmd_acc) 
                                       & (1U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__acc_read = ((IData)(vlTOPp->i2c_top__DOT__cmd_acc) 
                                      & (3U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__addr_phase = ((IData)(vlTOPp->i2c_top__DOT__acc_start) 
                                        | ((IData)(vlTOPp->i2c_top__DOT__acc_read) 
                                           & (~ (IData)(vlTOPp->i2c_top__DOT__read_cont))));
}

void Vi2c_top::_eval_initial(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_eval_initial\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

void Vi2c_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::final\n"); );
    // Variables
    Vi2c_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vi2c_top::_eval_settle(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_eval_settle\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

void Vi2c_top::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst_n = VL_RAND_RESET_I(1);
    cmd = VL_RAND_RESET_I(3);
    cmd_valid = VL_RAND_RESET_I(1);
    data_in = VL_RAND_RESET_I(8);
    sda_in = VL_RAND_RESET_I(1);
    cfg_wr = VL_RAND_RESET_I(1);
    cfg_sel = VL_RAND_RESET_I(1);
    cfg_data = VL_RAND_RESET_I(8);
    sda_oe = VL_RAND_RESET_I(1);
    scl_oe = VL_RAND_RESET_I(1);
    cov_state = VL_RAND_RESET_I(3);
    cov_cmd = VL_RAND_RESET_I(3);
    cov_prescale = VL_RAND_RESET_I(16);
    cov_addr = VL_RAND_RESET_I(7);
    cov_wr_byte = VL_RAND_RESET_I(8);
    cov_rd_byte = VL_RAND_RESET_I(8);
    cov_rd_valid = VL_RAND_RESET_I(1);
    cov_wr_valid = VL_RAND_RESET_I(1);
    cov_any_acc = VL_RAND_RESET_I(1);
    cov_nack = VL_RAND_RESET_I(1);
    cov_busy = VL_RAND_RESET_I(1);
    cov_bus_ctrl = VL_RAND_RESET_I(1);
    cov_dir = VL_RAND_RESET_I(1);
    cov_sda = VL_RAND_RESET_I(1);
    cov_hold = VL_RAND_RESET_I(1);
    cov_addr_ok_valid = VL_RAND_RESET_I(1);
    cov_addr_ok_class = VL_RAND_RESET_I(2);
    cov_cmd_cont = VL_RAND_RESET_I(1);
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
    i2c_top__DOT__clk = VL_RAND_RESET_I(1);
    i2c_top__DOT__rst_n = VL_RAND_RESET_I(1);
    i2c_top__DOT__cmd = VL_RAND_RESET_I(3);
    i2c_top__DOT__cmd_valid = VL_RAND_RESET_I(1);
    i2c_top__DOT__data_in = VL_RAND_RESET_I(8);
    i2c_top__DOT__sda_in = VL_RAND_RESET_I(1);
    i2c_top__DOT__cfg_wr = VL_RAND_RESET_I(1);
    i2c_top__DOT__cfg_sel = VL_RAND_RESET_I(1);
    i2c_top__DOT__cfg_data = VL_RAND_RESET_I(8);
    i2c_top__DOT__sda_oe = VL_RAND_RESET_I(1);
    i2c_top__DOT__scl_oe = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_state = VL_RAND_RESET_I(3);
    i2c_top__DOT__cov_cmd = VL_RAND_RESET_I(3);
    i2c_top__DOT__cov_prescale = VL_RAND_RESET_I(16);
    i2c_top__DOT__cov_addr = VL_RAND_RESET_I(7);
    i2c_top__DOT__cov_wr_byte = VL_RAND_RESET_I(8);
    i2c_top__DOT__cov_rd_byte = VL_RAND_RESET_I(8);
    i2c_top__DOT__cov_rd_valid = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_wr_valid = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_any_acc = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_nack = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_busy = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_bus_ctrl = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_dir = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_sda = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_hold = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_addr_ok_valid = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_addr_ok_class = VL_RAND_RESET_I(2);
    i2c_top__DOT__cov_cmd_cont = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_cfg_ok = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq1 = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq2 = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq3 = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq4 = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq5 = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq6 = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq7 = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq8 = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq9 = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq10 = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq11 = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq12 = VL_RAND_RESET_I(1);
    i2c_top__DOT__rst = VL_RAND_RESET_I(1);
    i2c_top__DOT__pend_code_q = VL_RAND_RESET_I(3);
    i2c_top__DOT__pend_data_q = VL_RAND_RESET_I(8);
    i2c_top__DOT__pend_valid_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__prescale_q = VL_RAND_RESET_I(16);
    i2c_top__DOT__st_q = VL_RAND_RESET_I(3);
    i2c_top__DOT__cov_cmd_q = VL_RAND_RESET_I(3);
    i2c_top__DOT__tx_addr_q = VL_RAND_RESET_I(7);
    i2c_top__DOT__cov_dir_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_wr_byte_q = VL_RAND_RESET_I(8);
    i2c_top__DOT__cov_rd_byte_q = VL_RAND_RESET_I(8);
    i2c_top__DOT__cov_rd_valid_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_wr_valid_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_any_acc_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_nack_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_sda_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_cmd_cont_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_cfg_ok_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__bc_d_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__tready_d_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__acc_d_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__busy_d_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_hold_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__hld_cnt_q = VL_RAND_RESET_I(16);
    i2c_top__DOT__hld_class_q = VL_RAND_RESET_I(2);
    i2c_top__DOT__cov_addr_ok_valid_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_addr_ok_class_q = VL_RAND_RESET_I(2);
    i2c_top__DOT__m_cmd_addr = VL_RAND_RESET_I(7);
    i2c_top__DOT__m_cmd_start = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_cmd_read = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_cmd_write = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_cmd_stop = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_cmd_valid = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_data_valid = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_cmd_ready = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_data_tready = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_busy = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_bus_control = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_bus_active = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_missed_ack = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_scl_o = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_scl_t = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_sda_o = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_sda_t = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_rd_tdata = VL_RAND_RESET_I(8);
    i2c_top__DOT__m_rd_tvalid = VL_RAND_RESET_I(1);
    i2c_top__DOT__m_rd_tlast = VL_RAND_RESET_I(1);
    i2c_top__DOT__scl_i_w = VL_RAND_RESET_I(1);
    i2c_top__DOT__sda_i_w = VL_RAND_RESET_I(1);
    i2c_top__DOT__cmd_acc = VL_RAND_RESET_I(1);
    i2c_top__DOT__data_acc = VL_RAND_RESET_I(1);
    i2c_top__DOT__acc_start = VL_RAND_RESET_I(1);
    i2c_top__DOT__acc_read = VL_RAND_RESET_I(1);
    i2c_top__DOT__acc_stop = VL_RAND_RESET_I(1);
    i2c_top__DOT__read_cont = VL_RAND_RESET_I(1);
    i2c_top__DOT__addr_phase = VL_RAND_RESET_I(1);
    i2c_top__DOT__any_acc = VL_RAND_RESET_I(1);
    i2c_top__DOT__pend_clear_w = VL_RAND_RESET_I(1);
    i2c_top__DOT__tready_rise = VL_RAND_RESET_I(1);
    i2c_top__DOT__e_nack = VL_RAND_RESET_I(1);
    i2c_top__DOT__e_txn_end = VL_RAND_RESET_I(1);
    i2c_top__DOT__busy_rise = VL_RAND_RESET_I(1);
    i2c_top__DOT__ok_a0 = VL_RAND_RESET_I(7);
    i2c_top__DOT__ok_a1 = VL_RAND_RESET_I(7);
    i2c_top__DOT__ok_a2 = VL_RAND_RESET_I(7);
    i2c_top__DOT__ok_a3 = VL_RAND_RESET_I(7);
    i2c_top__DOT__addr_nonzero = VL_RAND_RESET_I(1);
    i2c_top__DOT__addr_match = VL_RAND_RESET_I(1);
    i2c_top__DOT__match_class = VL_RAND_RESET_I(2);
    i2c_top__DOT__cov_seq1_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq2_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq3_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq4_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq5_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq6_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq7_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq8_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq9_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq10_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq11_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__cov_seq12_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__s1_stage_q = VL_RAND_RESET_I(2);
    i2c_top__DOT__s2_stage_q = VL_RAND_RESET_I(2);
    i2c_top__DOT__wr_run_q = VL_RAND_RESET_I(3);
    i2c_top__DOT__nack_flag_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__hold_run_q = VL_RAND_RESET_I(4);
    i2c_top__DOT__hold_p_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__pend_wait_q = VL_RAND_RESET_I(3);
    i2c_top__DOT__busy_run_q = VL_RAND_RESET_I(4);
    i2c_top__DOT__idle_run_q = VL_RAND_RESET_I(4);
    i2c_top__DOT__stop_el_q = VL_RAND_RESET_I(4);
    i2c_top__DOT__addr_seen_q = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__clk = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__rst = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_cmd_address = VL_RAND_RESET_I(7);
    i2c_top__DOT__u_master__DOT__s_axis_cmd_start = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_cmd_read = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_cmd_write = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_cmd_write_multiple = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_cmd_stop = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_cmd_valid = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_cmd_ready = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_data_tdata = VL_RAND_RESET_I(8);
    i2c_top__DOT__u_master__DOT__s_axis_data_tvalid = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_data_tready = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_data_tlast = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__m_axis_data_tdata = VL_RAND_RESET_I(8);
    i2c_top__DOT__u_master__DOT__m_axis_data_tvalid = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__m_axis_data_tready = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__m_axis_data_tlast = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__scl_i = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__scl_o = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__scl_t = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__sda_i = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__sda_o = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__sda_t = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__busy = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__bus_control = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__bus_active = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__missed_ack = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__prescale = VL_RAND_RESET_I(16);
    i2c_top__DOT__u_master__DOT__stop_on_idle = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__state_reg = VL_RAND_RESET_I(5);
    i2c_top__DOT__u_master__DOT__state_next = VL_RAND_RESET_I(5);
    i2c_top__DOT__u_master__DOT__phy_state_reg = VL_RAND_RESET_I(5);
    i2c_top__DOT__u_master__DOT__phy_state_next = VL_RAND_RESET_I(5);
    i2c_top__DOT__u_master__DOT__phy_start_bit = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__phy_stop_bit = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__phy_write_bit = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__phy_read_bit = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__phy_release_bus = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__phy_tx_data = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__phy_rx_data_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__phy_rx_data_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__addr_reg = VL_RAND_RESET_I(7);
    i2c_top__DOT__u_master__DOT__addr_next = VL_RAND_RESET_I(7);
    i2c_top__DOT__u_master__DOT__data_reg = VL_RAND_RESET_I(8);
    i2c_top__DOT__u_master__DOT__data_next = VL_RAND_RESET_I(8);
    i2c_top__DOT__u_master__DOT__last_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__last_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__mode_read_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__mode_read_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__mode_write_multiple_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__mode_write_multiple_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__mode_stop_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__mode_stop_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__delay_reg = VL_RAND_RESET_I(17);
    i2c_top__DOT__u_master__DOT__delay_next = VL_RAND_RESET_I(17);
    i2c_top__DOT__u_master__DOT__delay_scl_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__delay_scl_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__delay_sda_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__delay_sda_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__bit_count_reg = VL_RAND_RESET_I(4);
    i2c_top__DOT__u_master__DOT__bit_count_next = VL_RAND_RESET_I(4);
    i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_data_tready_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__s_axis_data_tready_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__m_axis_data_tdata_reg = VL_RAND_RESET_I(8);
    i2c_top__DOT__u_master__DOT__m_axis_data_tdata_next = VL_RAND_RESET_I(8);
    i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__m_axis_data_tlast_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__m_axis_data_tlast_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__scl_i_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__sda_i_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__scl_o_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__scl_o_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__sda_o_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__sda_o_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__last_scl_i_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__last_sda_i_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__busy_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__bus_active_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__bus_control_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__bus_control_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__missed_ack_reg = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__missed_ack_next = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__scl_posedge = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__scl_negedge = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__sda_posedge = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__sda_negedge = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__start_bit = VL_RAND_RESET_I(1);
    i2c_top__DOT__u_master__DOT__stop_bit = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
