// ============================================================================
// serv_public - dut/serv_mem_if.v
// 上游来源：https://github.com/olofk/serv（olofk/serv，main 分支，
// commit f200eb2ed7b69ac1c6b8eddd47654522aeee5ce8，2026-08-25）。
// 本文件为上游 rtl/serv_mem_if.v 原样保留（仅增加本来源注释与 timescale；
// 未作任何逻辑修改）。
// 许可：ISC License，Copyright 2019 Olof Kindgren <olof@award-winning.me>
// （原文见文件内 SPDX 头与包根目录 LICENSE）。
// 说明：本包由 dut/serv_top.v 实例化，参数选择见 dut/dut_spec.md §2.3。
// ============================================================================

`timescale 1 ns / 1 ps

/*
 * serv_mem_if.v : SERV memory interface
 *
 * SPDX-FileCopyrightText: 2018 Olof Kindgren <olof@award-winning.me>
 * SPDX-License-Identifier: ISC
 */
`default_nettype none
module serv_mem_if
  #(
    parameter [0:0] WITH_CSR = 1,
    parameter	    W = 1,
    parameter	    B = W-1
  )
  (
   input wire 	     i_clk,
   //State
   input wire [1:0]  i_bytecnt,
   input wire [1:0]  i_lsb,
   output wire 	     o_misalign,
   //Control
   input wire 	     i_signed,
   input wire 	     i_word,
   input wire 	     i_half,
   //MDU
   input wire 	     i_mdu_op,
   //Data
   input wire [B:0] i_bufreg2_q,
   output wire [B:0] o_rd,
   //External interface
   output wire [3:0] o_wb_sel);

   reg signbit;

   wire dat_valid =
	i_mdu_op |
	i_word |
	(i_bytecnt == 2'b00) |
	(i_half & !i_bytecnt[1]);

   assign o_rd = dat_valid ? i_bufreg2_q : {W{i_signed & signbit}};

   assign o_wb_sel[3] = (i_lsb == 2'b11) | i_word | (i_half & i_lsb[1]);
   assign o_wb_sel[2] = (i_lsb == 2'b10) | i_word;
   assign o_wb_sel[1] = (i_lsb == 2'b01) | i_word | (i_half & !i_lsb[1]);
   assign o_wb_sel[0] = (i_lsb == 2'b00);

   always @(posedge i_clk) begin
      if (dat_valid)
        signbit <= i_bufreg2_q[B];
   end

   /*
    mem_misalign is checked after the init stage to decide whether to do a data
    bus transaction or go to the trap state. It is only guaranteed to be correct
    at this time
    */
   assign o_misalign = WITH_CSR & ((i_lsb[0] & (i_word | i_half)) | (i_lsb[1] & i_word));

endmodule
