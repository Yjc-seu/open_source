// picorv32_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(10 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: ISC

module picorv_covergroup #(
    // Post-trap hold-window length; the evaluation platform bakes the real
    // constant in at compile time (mirroring picorv_top's TRAP_HOLD_N).
    parameter TRAP_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as picorv_top cov_* outputs)
    input logic [31:0]      cov_pc,
    input logic [31:0]      cov_instr,
    input logic [6:0]       cov_opcode,
    input logic [2:0]       cov_funct3,
    input logic [4:0]       cov_rd,
    input logic [4:0]       cov_rs1,
    input logic [4:0]       cov_rs2,
    input logic [15:0]      cov_mem_addr,
    input logic [15:0]      cov_mem_wdata,
    input logic [15:0]      cov_mem_rdata,
    input logic [3:0]       cov_mem_wstrb,
    input logic             cov_mem_rd,
    input logic             cov_mem_instr,
    input logic             cov_busy,
    input logic [7:0]       cov_instr_cnt,
    input logic             cov_trap,
    input logic             cov_hold,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,
    input logic             cov_branch_taken,
    input logic             cov_cfg_ok,

    // temporal sequence cover hits (from picorv_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        opcode_cp: coverpoint cov_opcode {
            bins op_lui      = {7'h37};
            bins op_auipc    = {7'h17};
            bins op_jal      = {7'h6F};
            bins op_jalr     = {7'h67};
            bins op_branch   = {7'h63};
            bins op_load     = {7'h03};
            bins op_store    = {7'h23};
            bins op_opimm    = {7'h13};
            bins op_op       = {7'h33};
            bins op_fence    = {7'h0F};
            bins op_system   = {7'h73};
            bins op_custom3  = {7'h7B};
        }
        funct3_cp: coverpoint cov_funct3 {
            bins f3_0 = {3'd0};
            bins f3_1 = {3'd1};
            bins f3_2 = {3'd2};
            bins f3_3 = {3'd3};
            bins f3_4 = {3'd4};
            bins f3_5 = {3'd5};
            bins f3_6 = {3'd6};
            bins f3_7 = {3'd7};
        }
        rd_cp: coverpoint cov_rd {
            bins rd_x0  = {5'd0};
            bins rd_x1  = {5'd1};
            bins rd_x31 = {5'd31};
        }
        rs1_cp: coverpoint cov_rs1 {
            bins rs1_x0  = {5'd0};
            bins rs1_x1  = {5'd1};
            bins rs1_x31 = {5'd31};
        }
        rs2_cp: coverpoint cov_rs2 {
            bins rs2_x0  = {5'd0};
            bins rs2_x1  = {5'd1};
            bins rs2_x31 = {5'd31};
        }
        mem_rd_cp: coverpoint cov_mem_rd {
            bins mrd_read  = {1'b1};
            bins mrd_write = {1'b0};
        }
        wstrb_cp: coverpoint cov_mem_wstrb {
            bins wst_none     = {4'd0};
            bins wst_lane0    = {4'd1};
            bins wst_lane1    = {4'd2};
            bins wst_lane2    = {4'd4};
            bins wst_lane3    = {4'd8};
            bins wst_hw_even  = {4'd3};
            bins wst_hw_odd   = {4'd12};
            bins wst_word     = {4'd15};
        }
    endgroup

    // =========================================================
    // boundary
    // =========================================================
    covergroup boundary_values @(posedge clk);
        pc_cp: coverpoint cov_pc {
            bins pc_start    = {32'd0};
            bins pc_second   = {32'd4};
            bins pc_mid      = {32'd2044};
            bins pc_lastword = {32'd4092};
        }
        mem_addr_cp: coverpoint cov_mem_addr {
            bins ma_zero        = {16'd0};
            bins ma_first_word  = {16'd4};
            bins ma_lastword_m2 = {16'hFFC8};
            bins ma_lastword    = {16'hFFFC};
        }
        wdata_cp: coverpoint cov_mem_wdata {
            bins wd_zero      = {16'd0};
            bins wd_one       = {16'd1};
            bins wd_upper_m1  = {16'hFFFE};
            bins wd_allones   = {16'hFFFF};
        }
        rdata_cp: coverpoint cov_mem_rdata {
            bins rd_zero      = {16'd0};
            bins rd_one       = {16'd1};
            bins rd_upper_m1  = {16'hFFFE};
            bins rd_allones   = {16'hFFFF};
        }
        instr_cnt_cp: coverpoint cov_instr_cnt {
            bins ic_zero = {8'd0};
            bins ic_one  = {8'd1};
            bins ic_254  = {8'd254};
            bins ic_255  = {8'd255};
        }
    endgroup

    // =========================================================
    // condition_combinational
    // =========================================================
    covergroup condition_combinational @(posedge clk);
        busy_cp: coverpoint cov_busy {
            bins busy_off = {1'b0};
            bins busy_on  = {1'b1};
        }
        trap_cp: coverpoint cov_trap {
            bins trap_off = {1'b0};
            bins trap_on  = {1'b1};
        }
        fetch_kind_cp: coverpoint cov_mem_instr {
            bins data_access  = {1'b0};
            bins fetch_access = {1'b1};
        }
        branch_dir_cp: coverpoint cov_branch_taken {
            bins branch_not_taken = {1'b0};
            bins branch_taken     = {1'b1};
        }
        cfg_ok_cp: coverpoint cov_cfg_ok {
            bins cfg_rejected = {1'b0};
            bins cfg_accepted = {1'b1};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
    endgroup

    // =========================================================
    // temporal_window (done_ok pulse class, iff valid)
    // =========================================================
    covergroup temporal_window @(posedge clk);
        done_ok_class_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
            bins done_ok_0 = {2'd0};
            bins done_ok_1 = {2'd1};
            bins done_ok_2 = {2'd2};
            bins done_ok_3 = {2'd3};
        }
    endgroup

    // =========================================================
    // cross_combinations
    // =========================================================
    covergroup cross_combinations @(posedge clk);
        opcode_x_funct3_cp: cross cov_opcode, cov_funct3 {
            bins op_add      = binsof(cov_opcode) intersect {7'h33} &&
                               binsof(cov_funct3) intersect {3'd0};
            bins op_srl      = binsof(cov_opcode) intersect {7'h33} &&
                               binsof(cov_funct3) intersect {3'd5};
            bins opimm_addi  = binsof(cov_opcode) intersect {7'h13} &&
                               binsof(cov_funct3) intersect {3'd0};
            bins opimm_xori  = binsof(cov_opcode) intersect {7'h13} &&
                               binsof(cov_funct3) intersect {3'd4};
            bins br_beq      = binsof(cov_opcode) intersect {7'h63} &&
                               binsof(cov_funct3) intersect {3'd0};
            bins br_bgeu     = binsof(cov_opcode) intersect {7'h63} &&
                               binsof(cov_funct3) intersect {3'd5};
            bins ld_lw       = binsof(cov_opcode) intersect {7'h03} &&
                               binsof(cov_funct3) intersect {3'd2};
            bins st_sw       = binsof(cov_opcode) intersect {7'h23} &&
                               binsof(cov_funct3) intersect {3'd2};
        }
        mem_rd_x_wstrb_cp: cross cov_mem_rd, cov_mem_wstrb {
            bins read_none     = binsof(cov_mem_rd) intersect {1'b1} &&
                                 binsof(cov_mem_wstrb) intersect {4'd0};
            bins write_lane0   = binsof(cov_mem_rd) intersect {1'b0} &&
                                 binsof(cov_mem_wstrb) intersect {4'd1};
            bins write_hw_even = binsof(cov_mem_rd) intersect {1'b0} &&
                                 binsof(cov_mem_wstrb) intersect {4'd3};
            bins write_word    = binsof(cov_mem_rd) intersect {1'b0} &&
                                 binsof(cov_mem_wstrb) intersect {4'd15};
        }
        busy_x_trap_cp: cross cov_busy, cov_trap {
            bins both_off  = binsof(cov_busy) intersect {1'b0} &&
                             binsof(cov_trap) intersect {1'b0};
            bins trap_idle = binsof(cov_busy) intersect {1'b0} &&
                             binsof(cov_trap) intersect {1'b1};
            bins busy_only = binsof(cov_busy) intersect {1'b1} &&
                             binsof(cov_trap) intersect {1'b0};
            bins busy_trap = binsof(cov_busy) intersect {1'b1} &&
                             binsof(cov_trap) intersect {1'b1};
        }
        trap_x_hold_cp: cross cov_trap, cov_hold {
            bins both_off  = binsof(cov_trap) intersect {1'b0} &&
                             binsof(cov_hold) intersect {1'b0};
            bins hold_only = binsof(cov_trap) intersect {1'b0} &&
                             binsof(cov_hold) intersect {1'b1};
            bins trap_only = binsof(cov_trap) intersect {1'b1} &&
                             binsof(cov_hold) intersect {1'b0};
        }
        hold_x_opcode_cp: cross cov_hold, cov_opcode {
            bins hold_system  = binsof(cov_hold) intersect {1'b1} &&
                                binsof(cov_opcode) intersect {7'h73};
            bins hold_opimm   = binsof(cov_hold) intersect {1'b1} &&
                                binsof(cov_opcode) intersect {7'h13};
            bins hold_custom3 = binsof(cov_hold) intersect {1'b1} &&
                                binsof(cov_opcode) intersect {7'h7B};
        }
        access_kind_cp: cross cov_mem_instr, cov_mem_rd {
            bins fetch = binsof(cov_mem_instr) intersect {1'b1} &&
                         binsof(cov_mem_rd) intersect {1'b1};
            bins load  = binsof(cov_mem_instr) intersect {1'b0} &&
                         binsof(cov_mem_rd) intersect {1'b1};
            bins store = binsof(cov_mem_instr) intersect {1'b0} &&
                         binsof(cov_mem_rd) intersect {1'b0};
        }
        busy_x_hold_cp: cross cov_busy, cov_hold {
            bins both_off  = binsof(cov_busy) intersect {1'b0} &&
                             binsof(cov_hold) intersect {1'b0};
            bins hold_idle = binsof(cov_busy) intersect {1'b0} &&
                             binsof(cov_hold) intersect {1'b1};
            bins busy_only = binsof(cov_busy) intersect {1'b1} &&
                             binsof(cov_hold) intersect {1'b0};
        }
    endgroup

    // =========================================================
    // sequence_hits (cov_seq1..12 from picorv_top monitors)
    // =========================================================
    covergroup sequence_hits @(posedge clk);
        seq_full_lifecycle_cp: coverpoint cov_seq1 {
            bins hit = {1'b1};
        }
        seq_branch_loop_cp: coverpoint cov_seq2 {
            bins hit = {1'b1};
        }
        seq_call_return_cp: coverpoint cov_seq3 {
            bins hit = {1'b1};
        }
        seq_ld_alu_st_cp: coverpoint cov_seq4 {
            bins hit = {1'b1};
        }
        seq_sequential_stream_cp: coverpoint cov_seq5 {
            bins hit = {1'b1};
        }
        seq_hold_persist_cp: coverpoint cov_seq6 {
            bins hit = {1'b1};
        }
        seq_hold_done_ok_cp: coverpoint cov_seq7 {
            bins hit = {1'b1};
        }
        seq_busy_cont_cp: coverpoint cov_seq8 {
            bins hit = {1'b1};
        }
        seq_trap_restart_cp: coverpoint cov_seq9 {
            bins hit = {1'b1};
        }
        seq_idle_stable_cp: coverpoint cov_seq10 {
            bins hit = {1'b1};
        }
        seq_quick_finish_cp: coverpoint cov_seq11 {
            bins hit = {1'b1};
        }
        seq_trap_consistent_cp: coverpoint cov_seq12 {
            bins hit = {1'b1};
        }
    endgroup

    // =========================================================
    // deep trackers (cross-cycle, mirror coverage_simulator.py 1:1)
    // =========================================================
    int ds_hold_run, ds_hold_max;
    int ds_class_first;
    bit ds_hold_hit, ds_class_switch, ds_opcode_hit;
    int ds_prev_cnt;
    int ds_opcodes[bit [6:0]];

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_hold_run <= 0; ds_hold_max <= 0;
            ds_hold_hit <= 0;
            ds_class_first <= -1;
            ds_class_switch <= 0;
            ds_prev_cnt <= -1;
            ds_opcodes.delete();
            ds_opcode_hit <= 0;
        end else begin
            // Q13: hold window length >= TRAP_HOLD_N - 1
            if (cov_hold) ds_hold_run <= ds_hold_run + 1;
            else          ds_hold_run <= 0;
            if (ds_hold_run > ds_hold_max) ds_hold_max <= ds_hold_run;
            if (ds_hold_max >= TRAP_HOLD_N - 1) ds_hold_hit <= 1;

            // Q14: two done_ok pulses with distinct classes
            if (cov_done_ok_valid) begin
                if (ds_class_first < 0)
                    ds_class_first <= cov_done_ok_class;
                else if (cov_done_ok_class != ds_class_first)
                    ds_class_switch <= 1;
            end

            // Q15: >=4 distinct opcode values across fetch completions
            if (ds_prev_cnt >= 0 && cov_instr_cnt != ds_prev_cnt) begin
                ds_opcodes[cov_opcode] = 1;
                if (ds_opcodes.num() >= 4) ds_opcode_hit <= 1;
            end
            ds_prev_cnt <= cov_instr_cnt;
        end
    end

    covergroup deep_trackers @(posedge clk);
        ds_hold_window_max_cp: coverpoint ds_hold_hit {
            bins hold_window_hit = {1'b1};
        }
        ds_done_ok_class_switch_cp: coverpoint ds_class_switch {
            bins class_switch_hit = {1'b1};
        }
        ds_opcode_diversity_cp: coverpoint ds_opcode_hit {
            bins opcode_div_hit = {1'b1};
        }
    endgroup

    // =========================================================
    // sva trackers (dataflow / timing, directive names match
    // assert_cov.svh 1:1)
    // =========================================================
    int df_busy_run, df_busy_max;
    int tp_hold_run, tp_hold_max;
    int tp_idle_run, tp_idle_max;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            df_busy_run <= 0; df_busy_max <= 0;
            tp_hold_run <= 0; tp_hold_max <= 0;
            tp_idle_run <= 0; tp_idle_max <= 0;
        end else begin
            if (cov_busy) df_busy_run <= df_busy_run + 1;
            else          df_busy_run <= 0;
            if (df_busy_run > df_busy_max) df_busy_max <= df_busy_run;

            if (cov_hold) tp_hold_run <= tp_hold_run + 1;
            else          tp_hold_run <= 0;
            if (tp_hold_run > tp_hold_max) tp_hold_max <= tp_hold_run;

            if (!cov_busy && !cov_hold && !cov_trap) tp_idle_run <= tp_idle_run + 1;
            else                                     tp_idle_run <= 0;
            if (tp_idle_run > tp_idle_max) tp_idle_max <= tp_idle_run;
        end
    end

    covergroup sva_dataflow_timing @(posedge clk);
        dataflow_busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[2:31]};
            bins busy4 = {[4:31]};
            bins busy8 = {[8:31]};
        }
        timing_active_dwell_cp: coverpoint df_busy_max {
            bins act1  = {[1:31]};
            bins act8  = {[8:31]};
            bins act16 = {[16:31]};
        }
        timing_hold_dwell_cp: coverpoint tp_hold_max {
            bins hold4    = {[4:65535]};
            bins holdfull = {[TRAP_HOLD_N-1:65535]};
        }
        timing_idle_dwell_cp: coverpoint tp_idle_max {
            bins idle4  = {[4:65535]};
            bins idle16 = {[16:65535]};
        }
    endgroup

endmodule
