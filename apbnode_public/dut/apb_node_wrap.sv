// ============================================================================
// apbnode_public - dut/apb_node_wrap.sv
// 上游原样文件：pulp-platform/apb_node（master 分支，src/apb_node_wrap.sv）
//   https://github.com/pulp-platform/apb_node
//   许可：Solderpad Hardware License v0.51（Apache-2.0 兼容）。
//   【本文件仅为来源完整性保留，不参与任何构建/仿真】：
//   它把 apb_node 包成 APB_BUS.Slave/Master 接口形态，依赖
//   pulp-platform/axi 仓库的 APB_BUS interface，Verilator 4.038 不支持
//   SystemVerilog interface 端口（也非 APB 标准组成部分），故竞赛 DUT 直接
//   使用扁平线网端口的 apb_node.sv（其内部逻辑与本文件完全一致，本文件只是
//   接口适配）。逻辑未作任何修改；仅文件头增加本注释与 `timescale。
// ============================================================================
`timescale 1ns / 1ps

// Copyright 2016 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

// Engineer:       Davide Rossi - davide.rossi@unibo.it
//                 Florian Zaruba - zarubaf@iis.ee.ethz.ch
// Design Name:    APB Bus
// Module Name:    apb_node_wrap
// Project Name:   PULP/Kerbin
// Language:       SystemVerilog
//
// Description:    This component implements a wrapper for a configurable APB node

module apb_node_wrap #(
        parameter int unsigned NB_MASTER      = 8,
        parameter int unsigned APB_DATA_WIDTH = 32,
        parameter int unsigned APB_ADDR_WIDTH = 32
)(
        input logic                                      clk_i,
        input logic                                      rst_ni,
        // Slave Port
        APB_BUS.Slave                                    apb_slave,
        // Master Ports
        APB_BUS.Master                                   apb_masters [NB_MASTER-1:0],
        // Configuration Port
        input  logic [NB_MASTER-1:0][APB_ADDR_WIDTH-1:0] start_addr_i,
        input  logic [NB_MASTER-1:0][APB_ADDR_WIDTH-1:0] end_addr_i
    );

    logic [NB_MASTER-1:0]                     penable;
    logic [NB_MASTER-1:0]                     pwrite;
    logic [NB_MASTER-1:0][APB_ADDR_WIDTH-1:0] paddr;
    logic [NB_MASTER-1:0]                     psel;
    logic [NB_MASTER-1:0][APB_DATA_WIDTH-1:0] pwdata;
    logic [NB_MASTER-1:0][APB_DATA_WIDTH-1:0] prdata;
    logic [NB_MASTER-1:0]                     pready;
    logic [NB_MASTER-1:0]                     pslverr;

    for (genvar i = 0; i < NB_MASTER; i++) begin
        assign apb_masters[i].penable = penable[i];
        assign apb_masters[i].pwrite  = pwrite[i];
        assign apb_masters[i].paddr   = paddr[i];
        assign apb_masters[i].psel    = psel[i];
        assign apb_masters[i].pwdata  = pwdata[i];
        assign prdata[i]              = apb_masters[i].prdata;
        assign pready[i]              = apb_masters[i].pready;
        assign pslverr[i]             = apb_masters[i].pslverr;
    end

    apb_node #(
        .NB_MASTER      ( NB_MASTER         ),
        .APB_DATA_WIDTH ( APB_DATA_WIDTH    ),
        .APB_ADDR_WIDTH ( APB_ADDR_WIDTH    )
    ) apb_node_i (
        .penable_i      ( apb_slave.penable ),
        .pwrite_i       ( apb_slave.pwrite  ),
        .paddr_i        ( apb_slave.paddr   ),
	.psel_i         ( apb_slave.psel    ),
        .pwdata_i       ( apb_slave.pwdata  ),
        .prdata_o       ( apb_slave.prdata  ),
        .pready_o       ( apb_slave.pready  ),
        .pslverr_o      ( apb_slave.pslverr ),

        .penable_o      ( penable           ),
        .pwrite_o       ( pwrite            ),
        .paddr_o        ( paddr             ),
        .psel_o         ( psel              ),
        .pwdata_o       ( pwdata            ),
        .prdata_i       ( prdata            ),
        .pready_i       ( pready            ),
        .pslverr_i      ( pslverr           ),

        .START_ADDR_i   ( start_addr_i      ),
        .END_ADDR_i     ( end_addr_i        )
    );
endmodule
