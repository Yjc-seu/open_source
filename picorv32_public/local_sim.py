#!/usr/bin/env python3
"""
picorv32_public - Black-box simulator (local_sim.py).
Python mirror of dut/picorv_top.v (upstream YosysHQ/picorv32, ISC) for local
development and evaluation. The mirror reproduces the RTL cycle-accurately at
the cov_* observation level, using the SAME upstream parameter set as
picorv_top.v (2-state semantics: Verilator evaluates uninitialized/X as 0).

Hidden parameters (op_ok_set, trap_hold_n) are injected externally; the public
default placeholder OP_OK_SET = [0,0,0,0] never matches (slot value 0 is
defined to never match), so done_ok is inert unless secrets are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : sel 0=cfg_addr[7:0] 1=cfg_addr[15:8]
                              2=memory byte write at cfg_addr (auto-increment)
                              (accepted only while not hold)
  - set_run(run)            : run level (1=release CPU, 0=hold in reset)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
  - inject_hidden_params(op_ok_set, trap_hold_n)
"""

from typing import Dict, List, Optional

# public placeholder values
PLACEHOLDER_OP_OK_SET = [0, 0, 0, 0]   # slot value 0 never matches
PLACEHOLDER_TRAP_HOLD_N = 16

# CPU states
ST_FETCH, ST_TRAP, ST_LD_RS1, ST_EXEC, ST_SHIFT, ST_STMEM, ST_LDMEM = range(7)

M32 = 0xFFFFFFFF


def _sx(v, bits):
    """sign-extend a two's complement value of `bits` width."""
    s = 1 << (bits - 1)
    m = (1 << bits) - 1
    v &= m
    return v - 2 * s if v & s else v


def _decode(w):
    """Full decode of instruction word w -> dict of flags (matches upstream
    coarse+fine decode; ENABLE_COUNTERS=0, ENABLE_IRQ=0)."""
    op = w & 0x7F
    f3 = (w >> 12) & 7
    f7 = (w >> 25) & 0x7F
    d = {"op": op, "f3": f3, "f7": f7}
    d["lui"] = 1 if op == 0x37 else 0
    d["auipc"] = 1 if op == 0x17 else 0
    d["jal"] = 1 if op == 0x6F else 0
    d["jalr"] = 1 if (op == 0x67 and f3 == 0) else 0
    d["beq"] = 1 if (op == 0x63 and f3 == 0) else 0
    d["bne"] = 1 if (op == 0x63 and f3 == 1) else 0
    d["blt"] = 1 if (op == 0x63 and f3 == 4) else 0
    d["bge"] = 1 if (op == 0x63 and f3 == 5) else 0
    d["bltu"] = 1 if (op == 0x63 and f3 == 6) else 0
    d["bgeu"] = 1 if (op == 0x63 and f3 == 7) else 0
    d["lb"] = 1 if (op == 0x03 and f3 == 0) else 0
    d["lh"] = 1 if (op == 0x03 and f3 == 1) else 0
    d["lw"] = 1 if (op == 0x03 and f3 == 2) else 0
    d["lbu"] = 1 if (op == 0x03 and f3 == 4) else 0
    d["lhu"] = 1 if (op == 0x03 and f3 == 5) else 0
    d["sb"] = 1 if (op == 0x23 and f3 == 0) else 0
    d["sh"] = 1 if (op == 0x23 and f3 == 1) else 0
    d["sw"] = 1 if (op == 0x23 and f3 == 2) else 0
    d["addi"] = 1 if (op == 0x13 and f3 == 0) else 0
    d["slti"] = 1 if (op == 0x13 and f3 == 2) else 0
    d["sltiu"] = 1 if (op == 0x13 and f3 == 3) else 0
    d["xori"] = 1 if (op == 0x13 and f3 == 4) else 0
    d["ori"] = 1 if (op == 0x13 and f3 == 6) else 0
    d["andi"] = 1 if (op == 0x13 and f3 == 7) else 0
    d["slli"] = 1 if (op == 0x13 and f3 == 1 and f7 == 0) else 0
    d["srli"] = 1 if (op == 0x13 and f3 == 5 and f7 == 0) else 0
    d["srai"] = 1 if (op == 0x13 and f3 == 5 and f7 == 0x20) else 0
    d["add"] = 1 if (op == 0x33 and f3 == 0 and f7 == 0) else 0
    d["sub"] = 1 if (op == 0x33 and f3 == 0 and f7 == 0x20) else 0
    d["sll"] = 1 if (op == 0x33 and f3 == 1 and f7 == 0) else 0
    d["slt"] = 1 if (op == 0x33 and f3 == 2 and f7 == 0) else 0
    d["sltu"] = 1 if (op == 0x33 and f3 == 3 and f7 == 0) else 0
    d["xor"] = 1 if (op == 0x33 and f3 == 4 and f7 == 0) else 0
    d["srl"] = 1 if (op == 0x33 and f3 == 5 and f7 == 0) else 0
    d["sra"] = 1 if (op == 0x33 and f3 == 5 and f7 == 0x20) else 0
    d["or"] = 1 if (op == 0x33 and f3 == 6 and f7 == 0) else 0
    d["and"] = 1 if (op == 0x33 and f3 == 7 and f7 == 0) else 0
    # ecall_ebreak: opcode 0x73 && !w[31:21] && !w[19:7]
    d["ecall_ebreak"] = 1 if (op == 0x73 and not ((w >> 21) & 0x7FF)
                              and not ((w >> 7) & 0x1FFF)) else 0
    d["fence"] = 1 if (op == 0x0F and f3 == 0) else 0
    known = (d["lui"] or d["auipc"] or d["jal"] or d["jalr"]
             or d["beq"] or d["bne"] or d["blt"] or d["bge"]
             or d["bltu"] or d["bgeu"]
             or d["lb"] or d["lh"] or d["lw"] or d["lbu"] or d["lhu"]
             or d["sb"] or d["sh"] or d["sw"]
             or d["addi"] or d["slti"] or d["sltiu"] or d["xori"]
             or d["ori"] or d["andi"] or d["slli"] or d["srli"] or d["srai"]
             or d["add"] or d["sub"] or d["sll"] or d["slt"] or d["sltu"]
             or d["xor"] or d["srl"] or d["sra"] or d["or"] or d["and"]
             or d["fence"])
    d["trap"] = 0 if known else 1
    return d


def _imm_j(w):
    """J-type immediate: {in[20],in[19:12],in[11],in[10:1],in[0]} from
    in = {w[31:12],1'b0}, sign-extended to 32 bits.
    in[20]=w[31], in[19:10]=w[30:21], in[9]=w[20], in[8:1]=w[19:12], in[0]=0
    -> imm = {w[31], w[30:23], w[22], w[21:12], 0} (standard RV32I J-imm)."""
    v = w >> 12
    out = (((v >> 19) & 1) << 20) | (((v >> 9) & 0x3FF) << 1) | \
          (((v >> 8) & 1) << 11) | ((v & 0xFF) << 12)
    return _sx(out, 21) & M32


class _Picorv32:
    """2-state mirror of upstream picorv32 (config baked in picorv_top.v)."""

    def __init__(self):
        # memory bus (top-visible)
        self.mem_valid = 0
        self.mem_instr = 0
        self.mem_addr = 0
        self.mem_wdata = 0
        self.mem_wstrb = 0
        self.trap = 0
        # pipeline
        self.regs = [0] * 32
        self.state = ST_FETCH
        self.reg_pc = 0
        self.reg_next_pc = 0
        self.reg_op1 = 0
        self.reg_op2 = 0
        self.reg_sh = 0
        self.reg_out = 0
        self.alu_out_q = 0
        self.latched_store = 0
        self.latched_stalu = 0
        self.latched_branch = 0
        self.latched_rd = 0
        self.latched_compr = 0
        self.latched_is_lu = 0
        self.latched_is_lh = 0
        self.latched_is_lb = 0
        self.decoder_trigger = 0
        self.decoder_pseudo_trigger = 0
        self.mem_do_rinst = 0
        self.mem_do_rdata = 0
        self.mem_do_wdata = 0
        self.mem_do_prefetch = 0
        self.mem_state = 0
        self.mem_rdata_q = 0
        self.mem_wordsize = 0
        # decode registers
        self.d = None            # dict from _decode (fine-decode source)
        self.i = {k: 0 for k in (
            "lui", "auipc", "jal", "jalr", "beq", "bne", "blt", "bge",
            "bltu", "bgeu", "lb", "lh", "lw", "lbu", "lhu", "sb", "sh", "sw",
            "addi", "slti", "sltiu", "xori", "ori", "andi", "slli", "srli",
            "srai", "add", "sub", "sll", "slt", "sltu", "xor", "srl", "sra",
            "or", "and", "ecall_ebreak", "fence")}
        self.is_branch = 0
        self.is_load = 0
        self.is_store = 0
        self.is_alu_imm = 0
        self.is_alu_reg = 0
        self.decoded_rd = 0
        self.decoded_rs1 = 0
        self.decoded_rs2 = 0
        self.decoded_imm = 0
        self.decoded_imm_j = 0
        # combo group registers
        self.is_lui_auipc_jal = 0
        self.is_lui_auipc_jal_jalr_addi_add_sub = 0
        self.is_slti_blt_slt = 0
        self.is_sltiu_bltu_sltu = 0
        self.is_lbu_lhu_lw = 0
        self.is_compare = 0
        self.is_slli_srli_srai = 0
        self.is_jalr_addi_slti_sltiu_xori_ori_andi = 0
        self.is_sll_srl_sra = 0

    # ------------------------------------------------------------------
    # combinational helpers (pre-posedge state passed via `p`)
    # ------------------------------------------------------------------
    @staticmethod
    def _alu_comb(p):
        """Returns (alu_out_0, alu_out) from pre-posedge state p."""
        i = p["i"]
        op1 = p["reg_op1"] & M32
        op2 = p["reg_op2"] & M32
        add_sub = (op1 - op2) & M32 if i["sub"] else (op1 + op2) & M32
        eq = 1 if op1 == op2 else 0
        lts = 1 if _sx(op1, 32) < _sx(op2, 32) else 0
        ltu = 1 if op1 < op2 else 0
        shl = (op1 << (op2 & 0x1F)) & M32
        sra_mode = i["sra"] or i["srai"]
        v33 = (op1 | 0x100000000) if (sra_mode and (op1 >> 31)) else op1
        shr = (v33 >> (op2 & 0x1F)) & M32
        a0 = 0
        if i["beq"]:
            a0 = eq
        elif i["bne"]:
            a0 = 1 - eq
        elif i["bge"]:
            a0 = 1 - lts
        elif i["bgeu"]:
            a0 = 1 - ltu
        elif p["is_slti_blt_slt"]:
            a0 = lts
        elif p["is_sltiu_bltu_sltu"]:
            a0 = ltu
        if p["is_lui_auipc_jal_jalr_addi_add_sub"]:
            out = add_sub
        elif p["is_compare"]:
            out = a0
        elif i["xori"] or i["xor"]:
            out = op1 ^ op2
        elif i["ori"] or i["or"]:
            out = op1 | op2
        elif i["andi"] or i["and"]:
            out = op1 & op2
        elif i["sll"] or i["slli"]:          # BARREL_SHIFTER=1
            out = shl
        elif i["srl"] or i["srli"] or i["sra"] or i["srai"]:
            out = shr
        else:
            out = 0                          # 'bx -> 0 (2-state)
        return a0, out

    @staticmethod
    def _mem_la(p):
        """look-ahead memory interface from pre-posedge state p
        (COMPRESSED_ISA=0)."""
        next_pc = ((p["reg_out"] & ~1) & M32) if (
            p["latched_store"] and p["latched_branch"]) else p["reg_next_pc"]
        la_read = p["mem_do_rinst"] or p["mem_do_prefetch"] or p["mem_do_rdata"]
        la_write = p["mem_do_wdata"]
        if p["mem_do_prefetch"] or p["mem_do_rinst"]:
            la_addr = (next_pc & ~3) & M32
        else:
            la_addr = (p["reg_op1"] & ~3) & M32
        ws = p["mem_wordsize"]
        if ws == 1:
            la_wdata = ((p["reg_op2"] & 0xFFFF) * 0x10001) & M32
            la_wstrb = 0xC if (p["reg_op1"] & 2) else 0x3
        elif ws == 2:
            la_wdata = ((p["reg_op2"] & 0xFF) * 0x01010101) & M32
            la_wstrb = 1 << (p["reg_op1"] & 3)
        else:
            la_wdata = p["reg_op2"] & M32
            la_wstrb = 0xF
        return la_read, la_write, la_addr, la_wdata, la_wstrb

    @staticmethod
    def _rdata_word(rdata, addr, ws):
        if ws == 1:
            return (rdata >> 16) & 0xFFFF if (addr & 2) else rdata & 0xFFFF
        if ws == 2:
            return (rdata >> (8 * (addr & 3))) & 0xFF
        return rdata & M32

    # ------------------------------------------------------------------
    def posedge(self, resetn, mem_rdata):
        """One posedge. `mem_rdata` is the combinational memory read for this
        cycle (pre-posedge). Mirrors the RTL always-block order exactly."""
        p = {
            "state": self.state,
            "decoder_trigger": self.decoder_trigger,
            "decoder_pseudo_trigger": self.decoder_pseudo_trigger,
            "mem_do_rinst": self.mem_do_rinst,
            "mem_do_rdata": self.mem_do_rdata,
            "mem_do_wdata": self.mem_do_wdata,
            "mem_do_prefetch": self.mem_do_prefetch,
            "mem_state": self.mem_state,
            "mem_valid": self.mem_valid,
            "mem_instr": self.mem_instr,
            "trap": self.trap,
            "reg_pc": self.reg_pc,
            "reg_next_pc": self.reg_next_pc,
            "reg_op1": self.reg_op1,
            "reg_op2": self.reg_op2,
            "reg_out": self.reg_out,
            "alu_out_q": self.alu_out_q,
            "latched_store": self.latched_store,
            "latched_stalu": self.latched_stalu,
            "latched_branch": self.latched_branch,
            "latched_rd": self.latched_rd,
            "mem_rdata_q": self.mem_rdata_q,
            "mem_wordsize": self.mem_wordsize,
            "i": dict(self.i),
            "is_branch": self.is_branch,
            "is_load": self.is_load,
            "is_store": self.is_store,
            "is_alu_imm": self.is_alu_imm,
            "is_lui_auipc_jal": self.is_lui_auipc_jal,
            "is_lui_auipc_jal_jalr_addi_add_sub":
                self.is_lui_auipc_jal_jalr_addi_add_sub,
            "is_slti_blt_slt": self.is_slti_blt_slt,
            "is_sltiu_bltu_sltu": self.is_sltiu_bltu_sltu,
            "is_lbu_lhu_lw": self.is_lbu_lhu_lw,
            "is_compare": self.is_compare,
            "is_slli_srli_srai": self.is_slli_srli_srai,
            "is_jalr_addi_slti_sltiu_xori_ori_andi":
                self.is_jalr_addi_slti_sltiu_xori_ori_andi,
            "is_sll_srl_sra": self.is_sll_srl_sra,
            "decoded_rd": self.decoded_rd,
            "decoded_rs1": self.decoded_rs1,
            "decoded_rs2": self.decoded_rs2,
            "decoded_imm": self.decoded_imm,
            "decoded_imm_j": self.decoded_imm_j,
        }
        mem_xfer = p["mem_valid"]                      # mem_ready == 1
        mem_done = bool(resetn) and (
            (mem_xfer and p["mem_state"] != 0 and
             (p["mem_do_rinst"] or p["mem_do_rdata"] or p["mem_do_wdata"]))
            or (p["mem_state"] == 3 and p["mem_do_rinst"]))

        # alu / la / writeback (combinational, pre-posedge)
        alu_out_0, alu_out = self._alu_comb(p)
        la_read, la_write, la_addr, la_wdata, la_wstrb = self._mem_la(p)
        wr = 0
        wrdata = 0
        if resetn and p["state"] == ST_FETCH:
            if p["latched_branch"]:
                wrdata = (p["reg_pc"] + 4) & M32
                wr = 1 if p["latched_rd"] else 0
            elif p["latched_store"]:
                wrdata = p["alu_out_q"] if p["latched_stalu"] else p["reg_out"]
                wr = 1 if p["latched_rd"] else 0

        # block 546: mem_rdata_q
        if mem_xfer:
            self.mem_rdata_q = mem_rdata & M32

        # combo group regs (from pre-posedge instr_*)
        i = p["i"]
        self.is_lui_auipc_jal = i["lui"] or i["auipc"] or i["jal"]
        self.is_lui_auipc_jal_jalr_addi_add_sub = (
            i["lui"] or i["auipc"] or i["jal"] or i["jalr"] or i["addi"]
            or i["add"] or i["sub"])
        self.is_slti_blt_slt = i["slti"] or i["blt"] or i["slt"]
        self.is_sltiu_bltu_sltu = i["sltiu"] or i["bltu"] or i["sltu"]
        self.is_lbu_lhu_lw = i["lbu"] or i["lhu"] or i["lw"]
        self.is_compare = (p["is_branch"] or i["slti"] or i["slt"]
                           or i["sltiu"] or i["sltu"])

        # coarse decode (mem_do_rinst && mem_done)
        if p["mem_do_rinst"] and mem_done:
            w = mem_rdata & M32
            d = _decode(w)
            self.i["lui"] = d["lui"]
            self.i["auipc"] = d["auipc"]
            self.i["jal"] = d["jal"]
            self.i["jalr"] = d["jalr"]
            self.is_branch = 1 if (w & 0x7F) == 0x63 else 0
            self.is_load = 1 if (w & 0x7F) == 0x03 else 0
            self.is_store = 1 if (w & 0x7F) == 0x23 else 0
            self.is_alu_imm = 1 if (w & 0x7F) == 0x13 else 0
            self.is_alu_reg = 1 if (w & 0x7F) == 0x33 else 0
            self.decoded_imm_j = _imm_j(w)
            self.decoded_rd = (w >> 7) & 0x1F
            self.decoded_rs1 = (w >> 15) & 0x1F
            self.decoded_rs2 = (w >> 20) & 0x1F

        # fine decode (decoder_trigger && !decoder_pseudo_trigger)
        if p["decoder_trigger"] and not p["decoder_pseudo_trigger"]:
            w = p["mem_rdata_q"] & M32
            d = _decode(w)
            for k in self.i:
                self.i[k] = d.get(k, 0)
            self.is_slli_srli_srai = d["slli"] or d["srli"] or d["srai"]
            self.is_jalr_addi_slti_sltiu_xori_ori_andi = (
                d["jalr"] or d["addi"] or d["slti"] or d["sltiu"] or d["xori"]
                or d["ori"] or d["andi"])
            self.is_sll_srl_sra = d["sll"] or d["srl"] or d["sra"]
            if d["jal"]:
                self.decoded_imm = self.decoded_imm_j
            elif d["lui"] or d["auipc"]:
                self.decoded_imm = ((w >> 12) << 12) & M32
            elif d["jalr"] or p["is_load"] or p["is_alu_imm"]:
                self.decoded_imm = _sx(w >> 20, 12) & M32
            elif (d["beq"] or d["bne"] or d["blt"] or d["bge"] or d["bltu"]
                  or d["bgeu"]):
                self.decoded_imm = _sx((((w >> 31) & 1) << 12)
                                       | (((w >> 7) & 1) << 11)
                                       | (((w >> 25) & 0x3F) << 5)
                                       | (((w >> 8) & 0xF) << 1), 13) & M32
            elif d["sb"] or d["sh"] or d["sw"]:
                self.decoded_imm = _sx((((w >> 25) & 0x7F) << 5)
                                       | ((w >> 7) & 0x1F), 12) & M32
            else:
                self.decoded_imm = 0

        # ---- main always block ----
        trap_out = 0
        self.decoder_trigger = 1 if (p["mem_do_rinst"] and mem_done) else 0
        self.decoder_pseudo_trigger = 0
        set_mem_do_rinst = 0
        set_mem_do_rdata = 0
        set_mem_do_wdata = 0

        if not resetn:
            self.reg_pc = 0
            self.reg_next_pc = 0
            self.latched_store = 0
            self.latched_stalu = 0
            self.latched_branch = 0
            self.latched_is_lu = 0
            self.latched_is_lh = 0
            self.latched_is_lb = 0
            self.state = ST_FETCH
        else:
            st = p["state"]
            i = p["i"]
            if st == ST_TRAP:
                trap_out = 1
            elif st == ST_FETCH:
                self.mem_do_rinst = 1 if not p["decoder_trigger"] else 0
                self.mem_wordsize = 0
                cur = p["reg_next_pc"] & M32
                if p["latched_branch"]:
                    cur = ((p["alu_out_q"] if p["latched_stalu"]
                            else p["reg_out"]) & ~1) & M32 \
                        if p["latched_store"] else p["reg_next_pc"]
                self.reg_pc = cur
                self.reg_next_pc = cur
                self.latched_store = 0
                self.latched_stalu = 0
                self.latched_branch = 0
                self.latched_rd = self.decoded_rd & 0x1F
                self.latched_compr = 0
                if p["decoder_trigger"]:
                    self.reg_next_pc = (cur + 4) & M32
                    if i["jal"]:
                        self.mem_do_rinst = 1
                        self.reg_next_pc = (cur + p["decoded_imm_j"]) & M32
                        self.latched_branch = 1
                    else:
                        self.mem_do_rinst = 0
                        self.mem_do_prefetch = 0 if i["jalr"] else 1
                        self.state = ST_LD_RS1
            elif st == ST_LD_RS1:
                self.reg_op1 = 0
                self.reg_op2 = 0
                rs1 = p["decoded_rs1"] & 0x1F
                rs2 = p["decoded_rs2"] & 0x1F
                cprs1 = self.regs[rs1] if rs1 else 0
                cprs2 = self.regs[rs2] if rs2 else 0
                if not (i["lui"] or i["auipc"] or i["jal"] or i["jalr"]
                        or i["beq"] or i["bne"] or i["blt"] or i["bge"]
                        or i["bltu"] or i["bgeu"]
                        or i["lb"] or i["lh"] or i["lw"] or i["lbu"] or i["lhu"]
                        or i["sb"] or i["sh"] or i["sw"]
                        or i["addi"] or i["slti"] or i["sltiu"] or i["xori"]
                        or i["ori"] or i["andi"] or i["slli"] or i["srli"]
                        or i["srai"] or i["add"] or i["sub"] or i["sll"]
                        or i["slt"] or i["sltu"] or i["xor"] or i["srl"]
                        or i["sra"] or i["or"] or i["and"] or i["fence"]):
                    self.state = ST_TRAP
                elif p["is_lui_auipc_jal"]:
                    self.reg_op1 = 0 if i["lui"] else p["reg_pc"] & M32
                    self.reg_op2 = p["decoded_imm"] & M32
                    self.mem_do_rinst = p["mem_do_prefetch"]
                    self.state = ST_EXEC
                elif p["is_load"]:
                    self.reg_op1 = cprs1 & M32
                    self.state = ST_LDMEM
                    self.mem_do_rinst = 1
                elif p["is_slli_srli_srai"]:      # BARREL_SHIFTER=1 -> ALU
                    self.reg_op1 = cprs1 & M32
                    self.reg_op2 = rs2
                    self.mem_do_rinst = p["mem_do_prefetch"]
                    self.state = ST_EXEC
                elif p["is_jalr_addi_slti_sltiu_xori_ori_andi"]:
                    self.reg_op1 = cprs1 & M32
                    self.reg_op2 = p["decoded_imm"] & M32
                    self.mem_do_rinst = p["mem_do_prefetch"]
                    self.state = ST_EXEC
                else:
                    self.reg_op1 = cprs1 & M32
                    self.reg_sh = cprs2 & M32
                    self.reg_op2 = cprs2 & M32
                    if p["is_store"]:
                        self.state = ST_STMEM
                        self.mem_do_rinst = 1
                    else:
                        self.mem_do_rinst = p["mem_do_prefetch"]
                        self.state = ST_EXEC
            elif st == ST_EXEC:
                self.reg_out = (p["reg_pc"] + p["decoded_imm"]) & M32
                if p["is_branch"]:
                    self.latched_rd = 0
                    self.latched_store = alu_out_0
                    self.latched_branch = alu_out_0
                    if mem_done:
                        self.state = ST_FETCH
                    if alu_out_0:
                        self.decoder_trigger = 0
                        set_mem_do_rinst = 1
                else:
                    self.latched_branch = i["jalr"]
                    self.latched_store = 1
                    self.latched_stalu = 1
                    self.state = ST_FETCH
            elif st == ST_SHIFT:
                # unreachable with BARREL_SHIFTER=1; mirror upstream anyway
                self.latched_store = 1
                if self.reg_sh == 0:
                    self.reg_out = self.reg_op1 & M32
                    self.mem_do_rinst = p["mem_do_prefetch"]
                    self.state = ST_FETCH
                elif self.reg_sh >= 4:
                    if i["slli"] or i["sll"]:
                        self.reg_op1 = (self.reg_op1 << 4) & M32
                    elif i["srai"] or i["sra"]:
                        self.reg_op1 = _sx(self.reg_op1, 32) >> 4 & M32
                    else:
                        self.reg_op1 = (self.reg_op1 >> 4) & M32
                    self.reg_sh = (self.reg_sh - 4) & 0x1F
                else:
                    if i["slli"] or i["sll"]:
                        self.reg_op1 = (self.reg_op1 << 1) & M32
                    elif i["srai"] or i["sra"]:
                        self.reg_op1 = _sx(self.reg_op1, 32) >> 1 & M32
                    else:
                        self.reg_op1 = (self.reg_op1 >> 1) & M32
                    self.reg_sh = (self.reg_sh - 1) & 0x1F
            elif st == ST_STMEM:
                if (not p["mem_do_prefetch"]) or mem_done:
                    if not p["mem_do_wdata"]:
                        self.mem_wordsize = 2 if i["sb"] else (1 if i["sh"] else 0)
                        self.reg_op1 = (p["reg_op1"] + p["decoded_imm"]) & M32
                        set_mem_do_wdata = 1
                    if (not p["mem_do_prefetch"]) and mem_done:
                        self.state = ST_FETCH
                        self.decoder_trigger = 1
                        self.decoder_pseudo_trigger = 1
            elif st == ST_LDMEM:
                self.latched_store = 1
                if (not p["mem_do_prefetch"]) or mem_done:
                    if not p["mem_do_rdata"]:
                        self.mem_wordsize = 2 if (i["lb"] or i["lbu"]) else (
                            1 if (i["lh"] or i["lhu"]) else 0)
                        self.latched_is_lu = p["is_lbu_lhu_lw"]
                        self.latched_is_lh = i["lh"]
                        self.latched_is_lb = i["lb"]
                        self.reg_op1 = (p["reg_op1"] + p["decoded_imm"]) & M32
                        set_mem_do_rdata = 1
                    if (not p["mem_do_prefetch"]) and mem_done:
                        w = self._rdata_word(mem_rdata & M32, p["reg_op1"] & M32,
                                             p["mem_wordsize"])
                        if self.latched_is_lu:
                            self.reg_out = w & M32
                        elif self.latched_is_lh:
                            self.reg_out = _sx(w & 0xFFFF, 16) & M32
                        elif self.latched_is_lb:
                            self.reg_out = _sx(w & 0xFF, 8) & M32
                        self.decoder_trigger = 1
                        self.decoder_pseudo_trigger = 1
                        self.state = ST_FETCH

        # ---- mem FSM ----
        if (not resetn) or p["trap"]:
            if not resetn:
                self.mem_state = 0
            self.mem_valid = 0                  # mem_ready == 1
        else:
            if la_read or la_write:
                self.mem_addr = la_addr
                self.mem_wstrb = (la_wstrb & (0xF if la_write else 0)) & 0xF
            if la_write:
                self.mem_wdata = la_wdata
            ms = p["mem_state"]
            if ms == 0:
                if (p["mem_do_prefetch"] or p["mem_do_rinst"]
                        or p["mem_do_rdata"]):
                    self.mem_valid = 1
                    self.mem_instr = 1 if (p["mem_do_prefetch"]
                                           or p["mem_do_rinst"]) else 0
                    self.mem_wstrb = 0
                    self.mem_state = 1
                if p["mem_do_wdata"]:
                    self.mem_valid = 1
                    self.mem_instr = 0
                    self.mem_state = 2
            elif ms == 1:
                if mem_xfer:
                    self.mem_valid = 0
                    self.mem_state = 0 if (p["mem_do_rinst"]
                                           or p["mem_do_rdata"]) else 3
            elif ms == 2:
                if mem_xfer:
                    self.mem_valid = 0
                    self.mem_state = 0
            elif ms == 3:
                if p["mem_do_rinst"]:
                    self.mem_state = 0

        # ---- mem_do clears + sets ----
        if (not resetn) or mem_done:
            self.mem_do_prefetch = 0
            self.mem_do_rinst = 0
            self.mem_do_rdata = 0
            self.mem_do_wdata = 0
        if set_mem_do_rinst:
            self.mem_do_rinst = 1
        if set_mem_do_rdata:
            self.mem_do_rdata = 1
        if set_mem_do_wdata:
            self.mem_do_wdata = 1

        # alu_out_q / trap / writeback
        self.alu_out_q = alu_out & M32
        self.trap = trap_out
        if wr and p["latched_rd"]:
            self.regs[p["latched_rd"] & 0x1F] = wrdata & M32


def _busy_after(insn):
    """busy_after(insn): countdown cycles after the instruction's fetch
    completes until the next memory access covers cov_busy. Mirrors the
    function in picorv_top.v (trap/illegal=2, jal=2, jalr=5, load=3,
    store=3, everything else=2)."""
    w = insn & M32
    op = w & 0x7F
    f3 = (w >> 12) & 7
    f7 = (w >> 25) & 0x7F
    if op == 0x63:
        return 2
    if op == 0x6F:
        return 2
    if op == 0x67:
        return 5 if f3 == 0 else 2
    if op == 0x03:
        return 3 if f3 in (0, 1, 2, 4, 5) else 2
    if op == 0x23:
        return 3 if f3 in (0, 1, 2) else 2
    if op == 0x13:
        if f3 in (0, 2, 3, 4, 6, 7) or (f3 == 1 and f7 == 0) \
                or (f3 == 5 and f7 in (0, 0x20)):
            return 2
        return 2
    if op == 0x33:
        if (f3 == 0 and f7 in (0, 0x20)) or (f3 == 1 and f7 == 0) \
                or (f3 in (2, 3, 4, 6, 7) and f7 == 0) \
                or (f3 == 5 and f7 in (0, 0x20)):
            return 2
        return 2
    if op == 0x0F:
        return 2
    if op in (0x37, 0x17):
        return 2
    return 2


class Picorv32Public:
    """Black-box simulator for picorv32_public (mirrors dut/picorv_top.v)."""

    def __init__(self,
                 op_ok_set: Optional[List[int]] = None,
                 trap_hold_n: Optional[int] = None):
        self.op_ok_set = list(op_ok_set) if op_ok_set else \
            list(PLACEHOLDER_OP_OK_SET)
        self.op_ok_set = [int(o) & 0x7F for o in self.op_ok_set]
        while len(self.op_ok_set) < 4:
            self.op_ok_set.append(0)
        self.trap_hold_n = int(trap_hold_n) if trap_hold_n is not None \
            else PLACEHOLDER_TRAP_HOLD_N
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, op_ok_set: List[int], trap_hold_n: int):
        self.op_ok_set = [int(o) & 0x7F for o in op_ok_set]
        while len(self.op_ok_set) < 4:
            self.op_ok_set.append(0)
        self.trap_hold_n = int(trap_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        self.cpu = _Picorv32()
        self.imem = [0] * 1024
        self.dmem = [0] * 1024
        self.cfg_addr = 0
        # action inputs (per-cycle)
        self._cfg_wr = 0
        self._cfg_sel = 0
        self._cfg_data = 0
        self.run = 0
        # cov registers
        self.cov_pc = 0
        self.cov_instr = 0
        self.cov_mem_addr = 0
        self.cov_mem_wdata = 0
        self.cov_mem_rdata = 0
        self.cov_mem_wstrb = 0
        self.cov_mem_rd = 1
        self.cov_mem_instr = 0
        self.cov_instr_cnt = 0
        self.cov_trap = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        self.cov_branch_taken = 0
        self.cov_cfg_ok = 0
        self.seq = {k: 0 for k in
                    ("cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4",
                     "cov_seq5", "cov_seq6", "cov_seq7", "cov_seq8",
                     "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12")}
        self.busy_cnt = 0
        self.trap_d = 0
        self.run_d = 0
        self.hold_d = 0
        self.hist0_pc = 0
        self.hist0_insn = 0
        self.hist1_pc = 0
        self.hist1_insn = 0
        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0
        # monitors
        self.prev_fetch_pc = 0
        self.s1_cfg = 0
        self.s1_run = 0
        self.s1_cnt = 0
        self.s2_back = 0
        self.s3_fwd = 0
        self.s4_state = 0
        self.s4_addr = 0
        self.s5_streak = 0
        self.s6_cnt = 0
        self.s8_cnt = 0
        self.s9_armed = 0
        self.s10_cnt = 0
        self.s11_armed = 0
        self.s11_cnt = 0
        self.s11_fetch = 0

    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """sel 0=cfg_addr[7:0] 1=cfg_addr[15:8] 2=memory byte write.
        Accepted only while not hold (gated in step, same as RTL)."""
        self._cfg_wr = 1
        self._cfg_sel = int(sel) & 7
        self._cfg_data = int(data) & 0xFF

    def set_run(self, run: int):
        self.run = 1 if int(run) & 1 else 0

    # ------------------------------------------------------------------
    def _cpu_resetn(self):
        return 1 if (self.run and not self.cov_hold) else 0

    def _match_class(self, opcode: int) -> int:
        for k in range(4):
            if opcode != 0 and opcode == self.op_ok_set[k]:
                return k
        return 3

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors picorv_top always blocks)."""
        cpu = self.cpu
        cpu_resetn = self._cpu_resetn()

        # ---- pre-posedge snapshots ----
        mem_valid_pre = cpu.mem_valid
        mem_instr_pre = cpu.mem_instr
        mem_addr_pre = cpu.mem_addr
        mem_wdata_pre = cpu.mem_wdata
        mem_wstrb_pre = cpu.mem_wstrb
        trap_pre = cpu.trap
        hold_pre = bool(self.cov_hold)
        run_rise = bool(self.run and not self.run_d)
        trap_rise = bool(trap_pre and not self.trap_d)
        cfg_evt = bool(self._cfg_wr and not hold_pre)
        fetch_done = bool(mem_valid_pre and mem_instr_pre)  # mem_ready==1
        load_done = bool(mem_valid_pre and not mem_instr_pre
                         and mem_wstrb_pre == 0)
        stor_done = bool(mem_valid_pre and not mem_instr_pre
                         and mem_wstrb_pre != 0)
        busy_pre = 1 if (cpu_resetn and (mem_valid_pre or self.busy_cnt > 0)) else 0
        done_ok_pre = bool(self.cov_done_ok_valid)
        prev_cov_instr = self.cov_instr
        prev_cov_pc = self.cov_pc
        prev_cov_opcode = prev_cov_instr & 0x7F

        # ---- memory read (combinational, pre-posedge) ----
        widx = (mem_addr_pre >> 2) & 0x3FF if mem_valid_pre else 0
        mem_rdata = (self.imem[widx] if mem_instr_pre
                     else self.dmem[widx]) & M32

        # ---- CPU posedge ----
        cpu.posedge(cpu_resetn, mem_rdata)

        # ---- CPU store write (access-completion posedge) ----
        if stor_done:
            w = (mem_addr_pre >> 2) & 0x3FF
            wd = mem_wdata_pre & M32
            ws = mem_wstrb_pre & 0xF
            if ws & 1:
                self.dmem[w] = (self.dmem[w] & ~0xFF) | (wd & 0xFF)
            if ws & 2:
                self.dmem[w] = (self.dmem[w] & ~0xFF00) | (wd & 0xFF00)
            if ws & 4:
                self.dmem[w] = (self.dmem[w] & ~0xFF0000) | (wd & 0xFF0000)
            if ws & 8:
                self.dmem[w] = (self.dmem[w] & ~0xFF000000) | (wd & 0xFF000000)

        # ---- cfg write (posedge; CPU read old value this cycle) ----
        if cfg_evt:
            sel = self._cfg_sel
            if sel == 0:
                self.cfg_addr = (self.cfg_addr & 0xFF00) | self._cfg_data
            elif sel == 1:
                self.cfg_addr = (self.cfg_addr & 0x00FF) | (self._cfg_data << 8)
            elif sel == 2:
                w = (self.cfg_addr >> 2) & 0x3FF
                lane = self.cfg_addr & 3
                if self.cfg_addr & 0x1000:
                    self.dmem[w] = (self.dmem[w]
                                    & ~(0xFF << (8 * lane))) \
                                   | (self._cfg_data << (8 * lane))
                else:
                    self.imem[w] = (self.imem[w]
                                    & ~(0xFF << (8 * lane))) \
                                   | (self._cfg_data << (8 * lane))
                self.cfg_addr = (self.cfg_addr + 1) & 0xFFFF

        # ---- cov registers ----
        self.cov_cfg_ok = 1 if cfg_evt else 0
        if fetch_done:
            self.hist1_pc = self.hist0_pc
            self.hist1_insn = self.hist0_insn
            self.hist0_pc = mem_addr_pre & M32
            self.hist0_insn = mem_rdata
            self.cov_pc = mem_addr_pre & M32
            self.cov_instr = mem_rdata
            self.cov_mem_addr = mem_addr_pre & 0xFFFF
            self.cov_mem_rdata = mem_rdata & 0xFFFF
            self.cov_mem_wstrb = 0
            self.cov_mem_rd = 1
            self.cov_mem_instr = 1
            self.cov_branch_taken = 1 if (
                prev_cov_opcode == 0x63
                and (mem_addr_pre & M32) != ((prev_cov_pc + 4) & M32)) else 0
            if self.cov_instr_cnt != 0xFF:
                self.cov_instr_cnt = (self.cov_instr_cnt + 1) & 0xFF
        if mem_valid_pre and not mem_instr_pre:
            self.cov_mem_addr = mem_addr_pre & 0xFFFF
            self.cov_mem_wdata = mem_wdata_pre & 0xFFFF
            self.cov_mem_rdata = mem_rdata & 0xFFFF
            self.cov_mem_wstrb = mem_wstrb_pre & 0xF
            self.cov_mem_rd = 1 if mem_wstrb_pre == 0 else 0
            self.cov_mem_instr = 0
        if trap_rise:
            self.cov_instr = self.hist1_insn
            self.cov_pc = self.hist1_pc

        # ---- busy countdown ----
        if not cpu_resetn:
            self.busy_cnt = 0
        else:
            if self.busy_cnt > 0:
                self.busy_cnt -= 1
            if fetch_done:
                ba = _busy_after(mem_rdata)
                if (prev_cov_opcode == 0x03) or (prev_cov_opcode == 0x23):
                    ba += 2
                self.busy_cnt = ba & 0xF

        # ---- trap / hold FSM ----
        self.cov_trap = 1 if trap_rise else 0
        self.cov_done_ok_valid = 0
        end_op = self.hist1_insn & 0x7F
        match0 = end_op != 0 and end_op == self.op_ok_set[0]
        match1 = end_op != 0 and end_op == self.op_ok_set[1]
        match2 = end_op != 0 and end_op == self.op_ok_set[2]
        match3 = end_op != 0 and end_op == self.op_ok_set[3]
        trap_match = match0 or match1 or match2 or match3
        trap_class = 0 if match0 else (1 if match1 else (2 if match2 else 3))
        if self.hld_state == 0:
            if trap_rise and trap_match:
                if self.trap_hold_n == 0:
                    self.cov_done_ok_valid = 1
                    self.cov_done_ok_class = trap_class
                else:
                    self.hld_state = 1
                    self.hld_cnt = self.trap_hold_n & 0xFFFF
                    self.hld_class = trap_class
                    self.cov_hold = 1
        elif self.hld_state == 1:
            if self.hld_cnt == 1:
                self.cov_hold = 0
                self.cov_done_ok_valid = 1
                self.cov_done_ok_class = self.hld_class
                self.hld_state = 2
            else:
                self.hld_cnt = (self.hld_cnt - 1) & 0xFFFF
        elif self.hld_state == 2:
            self.hld_state = 0

        # ---- monitors (pre-posedge snapshots) ----
        self._monitor_step(cfg_evt=cfg_evt, run_rise=run_rise,
                           fetch_done=fetch_done, load_done=load_done,
                           stor_done=stor_done, trap_rise=trap_rise,
                           busy_pre=busy_pre, hold_pre=hold_pre,
                           done_ok_pre=done_ok_pre,
                           trap_pre=trap_pre,
                           fetch_pc=mem_addr_pre & M32,
                           fetch_word=mem_rdata,
                           mem_addr=mem_addr_pre & M32)

        # ---- trailing registers ----
        self.trap_d = 1 if trap_pre else 0
        self.run_d = 1 if self.run else 0
        self.hold_d = 1 if hold_pre else 0
        self._cfg_wr = 0

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_evt, run_rise, fetch_done, load_done,
                      stor_done, trap_rise, busy_pre, hold_pre, done_ok_pre,
                      trap_pre, fetch_pc, fetch_word, mem_addr):
        """Mirror of the picorv_top temporal-sequence monitor (1:1).
        All inputs are pre-posedge snapshots."""
        s = self.seq
        for k in s:
            s[k] = 0

        # Q1: cfg 装载 -> run 释放 -> >=2 次取指 -> trap
        if cfg_evt:
            self.s1_cfg = 1
            self.s1_run = 0
            self.s1_cnt = 0
        elif self.s1_cfg and not self.s1_run and run_rise:
            self.s1_run = 1
        elif self.s1_cfg and self.s1_run and fetch_done and self.s1_cnt < 2:
            self.s1_cnt += 1
        if self.s1_cfg and self.s1_run and self.s1_cnt >= 2 and trap_rise:
            s["cov_seq1"] = 1
            self.s1_cfg = 0

        # Q2/Q3/Q5: 取指序列（比较一律用更新前的计数值，与 RTL 一致）
        s2_old = self.s2_back
        s5_old = self.s5_streak
        if fetch_done:
            if fetch_pc < self.prev_fetch_pc:
                if s2_old < 7:
                    self.s2_back = s2_old + 1
            if self.s3_fwd and fetch_pc < self.prev_fetch_pc:
                s["cov_seq3"] = 1
                self.s3_fwd = 0
            if fetch_pc > self.prev_fetch_pc \
                    and fetch_pc != (self.prev_fetch_pc + 4) & M32:
                self.s3_fwd = 1
            if fetch_pc == (self.prev_fetch_pc + 4) & M32:
                if s5_old < 8:
                    self.s5_streak = s5_old + 1
            else:
                self.s5_streak = 0
            self.prev_fetch_pc = fetch_pc
        if s2_old >= 3:
            s["cov_seq2"] = 1
        if s5_old >= 8:
            s["cov_seq5"] = 1

        # Q4: load -> ALU -> store 同址数据流
        if load_done:
            self.s4_state = 1
            self.s4_addr = mem_addr & 0xFFFF
        if fetch_done and self.s4_state == 1 \
                and (fetch_word & 0x7F) in (0x13, 0x33):
            self.s4_state = 2
        if stor_done and self.s4_state == 2 \
                and self.s4_addr == (mem_addr & 0xFFFF):
            s["cov_seq4"] = 1
            self.s4_state = 0

        # Q6: hold 连续 >=4 拍
        if hold_pre:
            if self.s6_cnt >= 3:
                s["cov_seq6"] = 1
            if self.s6_cnt < 0xFFFF:
                self.s6_cnt += 1
        else:
            self.s6_cnt = 0

        # Q7: done_ok 且前一拍 hold=1
        if done_ok_pre and self.hold_d:
            s["cov_seq7"] = 1

        # Q8: busy 连续 >=8 拍
        if busy_pre:
            if self.s8_cnt >= 7:
                s["cov_seq8"] = 1
            if self.s8_cnt < 31:
                self.s8_cnt += 1
        else:
            self.s8_cnt = 0

        # Q9: trap 后重启（之后取指完成 pc==0）
        if trap_rise:
            self.s9_armed = 1
        if fetch_done and self.s9_armed and fetch_pc == 0:
            s["cov_seq9"] = 1
            self.s9_armed = 0

        # Q10: 全局空闲连续 >=4 拍
        idle_now = (not busy_pre) and (not hold_pre) and (not trap_pre)
        if idle_now:
            if self.s10_cnt >= 3:
                s["cov_seq10"] = 1
            if self.s10_cnt < 15:
                self.s10_cnt += 1
        else:
            self.s10_cnt = 0

        # Q11: 快速完成（run 释放后 <=64 拍内、>=1 次取指后 trap）
        if run_rise:
            self.s11_armed = 1
            self.s11_cnt = 0
            self.s11_fetch = 0
        elif self.s11_armed:
            if self.s11_cnt < 127:
                self.s11_cnt += 1
            if fetch_done:
                self.s11_fetch = 1
            if self.s11_cnt > 64:
                self.s11_armed = 0
        if self.s11_armed and self.s11_fetch and trap_rise and self.s11_cnt <= 64:
            s["cov_seq11"] = 1
            self.s11_armed = 0

        # Q12: trap 一致性（trap 电平保持）
        if trap_pre and self.trap_d:
            s["cov_seq12"] = 1

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        cpu = self.cpu
        cpu_resetn = self._cpu_resetn()
        busy = 1 if (cpu_resetn and (cpu.mem_valid or self.busy_cnt > 0)) else 0
        ci = self.cov_instr & M32
        s = self.seq
        return {
            "cov_pc": self.cov_pc & M32,
            "cov_instr": ci,
            "cov_opcode": ci & 0x7F,
            "cov_funct3": (ci >> 12) & 7,
            "cov_rd": (ci >> 7) & 0x1F,
            "cov_rs1": (ci >> 15) & 0x1F,
            "cov_rs2": (ci >> 20) & 0x1F,
            "cov_mem_addr": self.cov_mem_addr & 0xFFFF,
            "cov_mem_wdata": self.cov_mem_wdata & 0xFFFF,
            "cov_mem_rdata": self.cov_mem_rdata & 0xFFFF,
            "cov_mem_wstrb": self.cov_mem_wstrb & 0xF,
            "cov_mem_rd": self.cov_mem_rd & 1,
            "cov_mem_instr": self.cov_mem_instr & 1,
            "cov_busy": busy,
            "cov_instr_cnt": self.cov_instr_cnt & 0xFF,
            "cov_trap": self.cov_trap & 1,
            "cov_hold": self.cov_hold & 1,
            "cov_done_ok_valid": self.cov_done_ok_valid & 1,
            "cov_done_ok_class": self.cov_done_ok_class & 3,
            "cov_branch_taken": self.cov_branch_taken & 1,
            "cov_cfg_ok": self.cov_cfg_ok & 1,
            "cov_seq1": s["cov_seq1"], "cov_seq2": s["cov_seq2"],
            "cov_seq3": s["cov_seq3"], "cov_seq4": s["cov_seq4"],
            "cov_seq5": s["cov_seq5"], "cov_seq6": s["cov_seq6"],
            "cov_seq7": s["cov_seq7"], "cov_seq8": s["cov_seq8"],
            "cov_seq9": s["cov_seq9"], "cov_seq10": s["cov_seq10"],
            "cov_seq11": s["cov_seq11"], "cov_seq12": s["cov_seq12"],
        }


if __name__ == "__main__":
    dut = Picorv32Public()
    print("picorv32_public local_sim loaded")
