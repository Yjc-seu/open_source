// ============================================================================
// serv_public - dut/serv_rf_ram.v
// 上游来源：https://github.com/olofk/serv（olofk/serv，main 分支，
// commit f200eb2ed7b69ac1c6b8eddd47654522aeee5ce8，2026-08-25）。
// 本文件为上游 rtl/serv_rf_ram.v 原样保留（仅增加本来源注释与 timescale；
// 未作任何逻辑修改）。
// 许可：ISC License，Copyright 2019 Olof Kindgren <olof@award-winning.me>
// （原文见文件内 SPDX 头与包根目录 LICENSE）。
// 说明：本包由 dut/serv_top.v 实例化，参数选择见 dut/dut_spec.md §2.3。
// ============================================================================

`timescale 1 ns / 1 ps

/*
 * serv_rf_ram.v : SRAM-based RF storage for SERV
 *
 * SPDX-FileCopyrightText: 2019 Olof Kindgren <olof@award-winning.me>
 * SPDX-License-Identifier: ISC
 */
module serv_rf_ram
  #(parameter width=0,
    parameter csr_regs=4,
    parameter depth=32*(32+csr_regs)/width)
   (input wire i_clk,
    input wire [$clog2(depth)-1:0] i_waddr,
    input wire [width-1:0] 	   i_wdata,
    input wire 			   i_wen,
    input wire [$clog2(depth)-1:0] i_raddr,
    input wire			   i_ren,
    output wire [width-1:0] 	   o_rdata);

   reg [width-1:0] 		   memory [0:depth-1];
   reg [width-1:0] 		   rdata ;

   always @(posedge i_clk) begin
      if (i_wen)
	memory[i_waddr] <= i_wdata;
      rdata <= i_ren ? memory[i_raddr] : {width{1'bx}};
   end

   /* Reads from reg x0 needs to return 0
    Check that the part of the read address corresponding to the register
    is zero and gate the output
    width LSB of reg index $clog2(width)
    2     4                1
    4     3                2
    8     2                3
    16    1                4
    32    0                5
    */
   reg regzero;

   always @(posedge i_clk)
     regzero <= !(|i_raddr[$clog2(depth)-1:5-$clog2(width)]);

   assign o_rdata = rdata & ~{width{regzero}};

`ifdef SERV_CLEAR_RAM
   integer i;
   initial
     for (i=0;i<depth;i=i+1)
       memory[i] = {width{1'd0}};
`endif
endmodule
