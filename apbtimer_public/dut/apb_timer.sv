// ============================================================================
// apbtimer_public - dut/apb_timer.sv
//
// Upstream source, kept verbatim (logic unmodified). Only two things were
// prepended: this attribution header and a `timescale directive.
//
// NOTE: this multi-timer APB wrapper is kept for reference / provenance only.
// apbtimer_top instantiates the single-timer leaf module `timer` directly
// (equivalent to TIMER_CNT=1, see dut_spec.md §1), because for TIMER_CNT=1
// the slave-address selection degenerates to an empty PADDR slice
// ($clog2(1)=0 -> PADDR[3:4]) which Verilator 4.038 cannot elaborate.
//
// Source: https://github.com/pulp-platform/apb_timer (branch: master)
//   file:  src/apb_timer.sv
// Copyright 2015 ETH Zurich and University of Bologna.
// License: Solderpad Hardware License v0.51 (SHL-0.51), see ../LICENSE.
//   (SHL-0.51 may optionally be treated as Apache-2.0.)
// ============================================================================

`timescale 1ns / 1ps

`define REGS_MAX_ADR             2'd2

module apb_timer
#(
    parameter APB_ADDR_WIDTH = 12,  //APB slaves are 4KB by default
    parameter TIMER_CNT = 2 // how many timers should be instantiated
)
(
    input  logic                      HCLK,
    input  logic                      HRESETn,
    input  logic [APB_ADDR_WIDTH-1:0] PADDR,
    input  logic               [31:0] PWDATA,
    input  logic                      PWRITE,
    input  logic                      PSEL,
    input  logic                      PENABLE,
    output logic               [31:0] PRDATA,
    output logic                      PREADY,
    output logic                      PSLVERR,

    output logic [(TIMER_CNT * 2) - 1:0] irq_o // overflow and cmp interrupt
);

    logic [TIMER_CNT-1:0] psel_int, pready, pslverr;
    logic [$clog2(TIMER_CNT) - 1:0] slave_address_int;
    logic [TIMER_CNT-1:0] [31:0] prdata;

    assign slave_address_int = PADDR[$clog2(TIMER_CNT)+ `REGS_MAX_ADR + 1:`REGS_MAX_ADR + 2];

    always_comb
    begin
        psel_int = '0;
        psel_int[slave_address_int] = PSEL;
    end

    // output mux
    always_comb
    begin

        if (psel_int != '0)
        begin
            PRDATA = prdata[slave_address_int];
            PREADY = pready[slave_address_int];
            PSLVERR = pslverr[slave_address_int];
        end
        else
        begin
            PRDATA = '0;
            PREADY = 1'b1;
            PSLVERR = 1'b0;
        end
    end


    genvar k;

    generate
    for(k = 0; k < TIMER_CNT; k++)
    begin : TIMER_GEN
      timer #(
          .APB_ADDR_WIDTH ( APB_ADDR_WIDTH )
      ) timer_i (
          .HCLK       ( HCLK          ),
          .HRESETn    ( HRESETn       ),

          .PADDR      ( PADDR        ),
          .PWDATA     ( PWDATA       ),
          .PWRITE     ( PWRITE       ),
          .PSEL       ( psel_int[k]  ),
          .PENABLE    ( PENABLE      ),
          .PRDATA     ( prdata[k]    ),
          .PREADY     ( pready[k]    ),
          .PSLVERR    ( pslverr[k]   ),

          .irq_o      ( irq_o[2*k+1 : 2*k] )
      );
    end
endgenerate
endmodule
