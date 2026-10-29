// ============================================================================
// apbspi_public - dut/spi_master_rx.sv
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

module spi_master_rx
(
    input  logic        clk,
    input  logic        rstn,
    input  logic        en,
    input  logic        rx_edge,
    output logic        rx_done,
    input  logic        sdi0,
    input  logic        sdi1,
    input  logic        sdi2,
    input  logic        sdi3,
    input  logic        en_quad_in,
    input  logic [15:0] counter_in,
    input  logic        counter_in_upd,
    output logic [31:0] data,
    input  logic        data_ready,
    output logic        data_valid,
    output logic        clk_en_o
);

  logic [31:0] data_int;
  logic [31:0] data_int_next;
  logic [15:0] counter;
  logic [15:0] counter_trgt;
  logic [15:0] counter_next;
  logic [15:0] counter_trgt_next;
  logic        done;
  logic        reg_done;
  enum logic [1:0] { IDLE, RECEIVE, WAIT_FIFO, WAIT_FIFO_DONE } rx_CS, rx_NS;


  assign reg_done  = (!en_quad_in && (counter[4:0] == 5'b11111)) || (en_quad_in && (counter[2:0] == 3'b111));

  assign data = data_int_next;
  assign rx_done = done;

  always_comb
  begin
    if (counter_in_upd)
      counter_trgt_next = (en_quad_in) ? {2'b00,counter_in[15:2]} : counter_in;
    else
      counter_trgt_next = counter_trgt;
  end

  assign done = (counter == counter_trgt-1) && rx_edge;

  always_comb
  begin
    rx_NS         = rx_CS;
    clk_en_o      = 1'b0;
    data_int_next = data_int;
    data_valid    = 1'b0;
    counter_next  = counter;

    case (rx_CS)
      IDLE: begin
        clk_en_o = 1'b0;

        // check first if there is available space instead of later
        if (en) begin
          rx_NS = RECEIVE;
        end
      end

      RECEIVE: begin
        clk_en_o = 1'b1;

        if (rx_edge) begin
          counter_next = counter + 1;

          if (en_quad_in)
            data_int_next = {data_int[27:0],sdi3,sdi2,sdi1,sdi0};
          else
            data_int_next = {data_int[30:0],sdi1};

          if (rx_done) begin
            counter_next = 0;
            data_valid   = 1'b1;

            if (data_ready)
              rx_NS = IDLE;
            else
              rx_NS = WAIT_FIFO_DONE;
          end else if (reg_done) begin
            data_valid = 1'b1;

            if (~data_ready) begin
              // no space in the FIFO, wait for free space
              clk_en_o = 1'b0;
              rx_NS    = WAIT_FIFO;
            end
          end
        end
      end

      WAIT_FIFO_DONE: begin
        data_valid = 1'b1;
        if (data_ready)
          rx_NS = IDLE;
      end

      WAIT_FIFO: begin
        data_valid = 1'b1;
        if (data_ready)
          rx_NS = RECEIVE;
      end
    endcase
  end


  always_ff @(posedge clk, negedge rstn)
  begin
    if (rstn == 0)
    begin
      counter      <= 0;
      counter_trgt <= 'h8;
      data_int     <= '0;
      rx_CS        <= IDLE;
    end
    else
    begin
      counter      <= counter_next;
      counter_trgt <= counter_trgt_next;
      data_int     <= data_int_next;
      rx_CS        <= rx_NS;
    end
  end

endmodule
