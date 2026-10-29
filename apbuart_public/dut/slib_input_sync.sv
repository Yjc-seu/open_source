// ============================================================================ // 来源: https://github.com/pulp-platform/apb_uart  (tag v0.2.1, src/slib_input_sync.sv) // 仓库许可: Solderpad Hardware License v0.51 (SHL-0.51)，见仓库 LICENSE； //          本文件体内保留上游原 LGPL-2.1 头注释（源自 Sebastian Witt 的 //          uart16750 VHDL->SystemVerilog 转换谱系，见下方原注释）。 // 本文件自上游原样保留，未作任何逻辑修改；仅增加此来源说明注释与 timescale。 // ============================================================================  	imescale 1ns / 1ps //
// UART 16750
//
// Converted to System Verilog by Jonathan Kimmitt
// This version has been partially checked with formality but some bugs remain
// Original Author:   Sebastian Witt
// Date:     14.03.2019
// Version:  1.6
//
// History:  1.0 - Initial version
//           1.1 - THR empty interrupt register connected to RST
//           1.2 - Registered outputs
//           1.3 - Automatic flow control
//           1.4 - De-assert IIR FIFO64 when FIFO is disabled
//           1.5 - Inverted low active outputs when RST is active
//           1.6 - Converted to System Verilog
//
//
// This code is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the
// Free Software  Foundation, Inc., 59 Temple Place, Suite 330,
// Boston, MA  02111-1307  USA
//

module slib_input_sync(
	input wire		CLK,
	input wire		RST,
	input wire		D,
	output logic		Q); // 507
/* design slib_input_sync */
/* architecture rtl */
typedef enum {FALSE,TRUE} bool_t; // 527
reg [1:0] iD; // 605

always @(posedge CLK or posedge RST)
  begin
     if ((RST ==  1'b1))
       begin
          /* block const 263 */
          iD <= (0<<1)|(0<<0);
       end
     else
       begin
          iD[0] <= D;
          iD[1] <= iD[0];       
       end
  end

assign /*432*/ Q = iD[1]; // 434
endmodule // slib_input_sync
