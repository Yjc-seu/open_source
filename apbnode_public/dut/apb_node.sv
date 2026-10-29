// ============================================================================
// apbnode_public - dut/apb_node.sv
// 上游原样文件：pulp-platform/apb_node（master 分支，src/apb_node.sv）
//   https://github.com/pulp-platform/apb_node
//   许可：Solderpad Hardware License v0.51（Apache-2.0 兼容，本包根目录
//   SHL-0.51-UPSTREAM.txt 为上游 LICENSE 全文）。
//   文件内容未作任何逻辑修改；仅在文件头增加本来源注释块与 `timescale
//   编译指令（竞赛 DUT 包装要求）。模块功能：APB 地址解码节点——
//   单 APB 从端口按 START_ADDR_i/END_ADDR_i 地址区间路由到 NB_MASTER 个
//   主端口（纯组合逻辑，多个区间同时命中时响应取最后一个命中的主端口，
//   属上游原始行为）。
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
// Module Name:    apb_node
// Project Name:   PULP/Kerbin
// Language:       SystemVerilog
//
// Description:    This component implements a configurable APB node

module apb_node #(
        parameter int unsigned NB_MASTER      = 8,
        parameter int unsigned APB_DATA_WIDTH = 32,
        parameter int unsigned APB_ADDR_WIDTH = 32
)(
        // SLAVE PORT
        input logic 					 penable_i,
        input logic 					 pwrite_i,
        input logic [APB_ADDR_WIDTH-1:0] 		 paddr_i,
        input logic                                      psel_i,
        input logic [APB_DATA_WIDTH-1:0] 		 pwdata_i,
        output logic [APB_DATA_WIDTH-1:0] 		 prdata_o,
        output logic 					 pready_o,
        output logic 					 pslverr_o,

        // MASTER PORTS
        output logic [NB_MASTER-1:0] 			 penable_o,
        output logic [NB_MASTER-1:0] 			 pwrite_o,
        output logic [NB_MASTER-1:0][APB_ADDR_WIDTH-1:0] paddr_o,
        output logic [NB_MASTER-1:0] 			 psel_o,
        output logic [NB_MASTER-1:0][APB_DATA_WIDTH-1:0] pwdata_o,
        input logic [NB_MASTER-1:0][APB_DATA_WIDTH-1:0]  prdata_i,
        input logic [NB_MASTER-1:0] 			 pready_i,
        input logic [NB_MASTER-1:0] 			 pslverr_i,

        // CONFIGURATION PORT
        input logic [NB_MASTER-1:0][APB_ADDR_WIDTH-1:0]  START_ADDR_i,
        input logic [NB_MASTER-1:0][APB_ADDR_WIDTH-1:0]  END_ADDR_i
    );

    always_comb begin : match_address
        psel_o = '0;

        // generate the select signal based on the supplied address
        for (int unsigned i = 0; i < NB_MASTER; i++)
            psel_o[i]  =  psel_i & (paddr_i >= START_ADDR_i[i]) && (paddr_i <= END_ADDR_i[i]);
    end

    always_comb begin
        // default assignment - keep silent by default
        penable_o = '0;
        pwrite_o  = '0;
        paddr_o   = '0;
        pwdata_o  = '0;
        prdata_o  = '0;
        pready_o  = 1'b0;
        pslverr_o = 1'b0;
        // select the right master
        for (int unsigned i = 0; i < NB_MASTER; i++) begin
            // master j was selected because the address matched int the generate statement above
            if (psel_o[i]) begin
                // master out - slave in
                penable_o[i] = penable_i;
                pwrite_o[i]  = pwrite_i;
                paddr_o[i]   = paddr_i;
                pwdata_o[i]  = pwdata_i;
                // master in - slave out
                prdata_o     = prdata_i[i];
                pready_o     = pready_i[i];
                pslverr_o    = pslverr_i[i];
            end
        end
    end
endmodule
