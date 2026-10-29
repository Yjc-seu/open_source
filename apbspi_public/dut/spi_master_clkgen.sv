// ============================================================================
// apbspi_public - dut/spi_master_clkgen.sv
// UPSTREAM SOURCE, verbatim (no logic changes).
//   Repo:   https://github.com/pulp-platform/axi_spi_master
//   Origin: pulp-platform/axi_spi_master @ ee21907 (2019)
//   Files of apb_spi_master are symlinked to the axi_spi_master IP; the
//   linked targets were materialized from the axi_spi_master repo commit
//   ee219078353a76e468674c25675f5b7fe5f51127 (last version shipped with
//   apb_spi_master v0.1.0).
//   License: Solderpad Hardware License v0.51 (see LICENSE).
// Only the header above was added; the body below is byte-identical to
// upstream, except for the timescale directive prepended after the header.
// ============================================================================

`timescale 1ns / 1ps

// Copyright 2015 ETH Zurich and University of Bologna.
// Copyright and related rights are licensed under the Solderpad Hardware
// License, Version 0.51 (the “License”); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://solderpad.org/licenses/SHL-0.51. Unless required by applicable law
// or agreed to in writing, software, hardware and materials distributed under
// this License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

module spi_master_clkgen
(
    input  logic                        clk,
    input  logic                        rstn,
    input  logic                        en,
    input  logic          [7:0]         clk_div,
    input  logic                        clk_div_valid,
    output logic                        spi_clk,
    output logic                        spi_fall,
    output logic                        spi_rise
);

    logic [7:0] counter_trgt;
    logic [7:0] counter_trgt_next;
    logic [7:0] counter;
    logic [7:0] counter_next;

    logic       spi_clk_next;
    logic       running;

    always_comb
    begin
            spi_rise = 1'b0;
            spi_fall = 1'b0;
            if (clk_div_valid)
                counter_trgt_next = clk_div;
            else
                counter_trgt_next = counter_trgt;

            if (counter == counter_trgt)
            begin
                counter_next = 0;
                spi_clk_next = ~spi_clk;
                if(spi_clk == 1'b0)
                    spi_rise = running;
                else
                    spi_fall = running;
            end
            else
            begin
                counter_next = counter + 1;
                spi_clk_next = spi_clk;
            end
    end

    always_ff @(posedge clk, negedge rstn)
    begin
        if (rstn == 1'b0)
        begin
            counter_trgt <= 'h0;
            counter      <= 'h0;
            spi_clk      <= 1'b0;
            running      <= 1'b0;
        end
        else
        begin
            counter_trgt <= counter_trgt_next;
            if ( !((spi_clk==1'b0)&&(~en)) )
            begin
                running <= 1'b1;
                spi_clk <= spi_clk_next;
                counter <= counter_next;
            end
            else
                running <= 1'b0;
        end
    end



endmodule
