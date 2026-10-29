// ============================================================================ // 来源: https://github.com/pulp-platform/apb_uart  (tag v0.2.1, src/slib_mv_filter.sv) // 仓库许可: Solderpad Hardware License v0.51 (SHL-0.51)，见仓库 LICENSE； //          本文件体内保留上游原 LGPL-2.1 头注释（源自 Sebastian Witt 的 //          uart16750 VHDL->SystemVerilog 转换谱系，见下方原注释）。 // 本文件自上游原样保留，未作任何逻辑修改；仅增加此来源说明注释与 timescale。 // ============================================================================  	imescale 1ns / 1ps //
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

module slib_mv_filter #(parameter WIDTH = 4, THRESHOLD = 10) (
	input wire		CLK,
	input wire		RST,
	input wire		SAMPLE,
	input wire		CLEAR,
	input wire		D,
	output logic		Q); // 507
/* design slib_mv_filter */
/* architecture rtl */
typedef enum {FALSE,TRUE} bool_t; // 527
reg [WIDTH:0] iCounter; // 605
reg iQ; // 612

always @(posedge CLK or posedge RST)
  if (RST)
    begin
       /* block const 263 */
       iCounter <= 0;
       iQ <=  1'b0; // 413
    end
  else
    begin
       if (iCounter >= THRESHOLD)
         begin
            iQ <=  1'b1; // 413
         end
       else
         begin
            if ((SAMPLE ==  1'b1 && D ==  1'b1))
              begin
                 iCounter <= iCounter + 1; // 413
              end
         end
       if ((CLEAR ==  1'b1))
         begin
            /* block const 263 */
            iCounter <= 0;
            iQ <=  1'b0; // 413
         end
    end

assign /*432*/ Q = iQ; // 434

endmodule // slib_mv_filter
