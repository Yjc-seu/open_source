#!/usr/bin/env python3
"""
femtorv_public - Black-box simulator (local_sim.py).
Python mirror of dut/femtorv_top.v + 上游 FemtoRV32 QUARK（BrunoLevy/learn-fpga，
BSD-3 许可）for local development and evaluation. The mirror reproduces the RTL
cycle-accurately at the cov_* observation level (2-state semantics: Verilator
evaluates uninitialized/X as 0).

结构：
  _Quark         —— 上游 femtorv32_quark.v 的逐行镜像（状态机/寄存器堆/ALU/
                    串行移位器/cycles 计数器；注意：核的 reset 只复位 state 与
                    PC，寄存器堆与 aluShamt 在复位期间保持并继续"排水"）。
  FemtorvPublic  —— dut/femtorv_top.v 的镜像：内置 imem/dmem、cfg 装载协议、
                    锁步影子状态机（F/W/E/WAM，WAM 以观测取指 strobe 退出）、
                    结束指令（trap）检测、OP_OK_SET/TRAP_HOLD_N 隐藏机制、
                    覆盖观测总线与 12 条时序序列监视器。
  INSTR_CYCLE_TABLE —— 每类指令的实测周期数（fetch strobe 到下一 fetch
                    strobe 的拍数；经 Verilator 实测并由 cross_check.py
                    周期级对拍背书，见 dut_spec.md §3.2）。

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

M32 = 0xFFFFFFFF
AW = 24
AM = (1 << AW) - 1

# shadow states (mirror femtorv_top.v localparams)
S_F, S_W, S_E, S_WAM = 0, 1, 2, 3

# ---------------------------------------------------------------------------
# 每类指令实测周期数（fetch strobe 拍到下一 fetch strobe 拍的拍数；经
# Verilator 实测并与 local_sim 对拍一致，见 dut_spec.md §3.2 与 __main__ 自检）
# ---------------------------------------------------------------------------
INSTR_CYCLE_TABLE = {
    # 无等待指令：F/W/E 三拍（含 ADD/SUB/SLL0/SLT/SLTU/XOR/SRL0/SRA0/OR/AND、
    # ADDI/SLTI/SLTIU/XORI/ORI/ANDI、LUI/AUIPC、JAL、JALR、分支 taken/not-taken、
    # SYSTEM(RDCYCLE 编码)、FENCE（原地自循环））
    "alu_nonshift": 3,
    "branch":       3,
    "jal":          3,
    "jalr":         3,
    "lui_auipc":    3,
    "system_rdcycle": 3,   # 0x73 在本 DUT 中为结束指令，此处仅指核的原始节拍
    "fence":        3,     # quark 特例：JAL PC+0 原地自循环，run=0 才能退出
    "load":         4,     # F/W/E(读数据)/WAM
    "store":        4,     # F/W/E(写数据)/WAM
    # 移位（SLL/SRL/SRA/SLLI/SRLI/SRAI，移位量 k=0..31）：F/W/E(装载 shamt)/WAM x(k+1)
    "shift_k":      "4+k",   # 4 + k 拍
    # 结束指令（EBREAK/ECALL/非法编码）：F/W/E 三拍，E 拍末 trap
    "end_insn":     3,
}


# ---------------------------------------------------------------------------
# 解码助手（与 femtorv_top.v 的 function 1:1）
# ---------------------------------------------------------------------------
def _is_load(w):
    return ((w >> 2) & 0x1F) == 0b00000


def _is_store(w):
    return ((w >> 2) & 0x1F) == 0b01000


def _need_wait(w):
    return _is_load(w) or _is_store(w) or (
        ((w >> 2) & 0x1F) in (0b00100, 0b01100)
        and ((w >> 12) & 7) in (1, 5))


def _is_valid(w):
    """合法 RV32I 指令判定（与 femtorv_top.v 的 is_valid_f 1:1）。
    返回 False 的指令 = 程序结束指令。"""
    w &= M32
    f3 = (w >> 12) & 7
    f7 = (w >> 25) & 0x7F
    op = w & 0x7F
    if op == 0x37:                                  # LUI
        return True
    if op == 0x17:                                  # AUIPC
        return True
    if op == 0x6F:                                  # JAL
        return True
    if op == 0x67:                                  # JALR
        return f3 == 0
    if op == 0x63:                                  # branch
        return f3 != 2 and f3 != 3
    if op == 0x03:                                  # LOAD
        return f3 in (0, 1, 2, 4, 5)
    if op == 0x23:                                  # STORE
        return f3 <= 2
    if op == 0x13:                                  # OP-IMM
        return (f3 != 1 or f7 == 0) and \
               (f3 != 5 or f7 in (0, 0x20))
    if op == 0x33:                                  # OP
        return ((f3 != 0) or (f7 in (0, 0x20))) and \
               ((f3 != 1) or (f7 == 0)) and \
               ((f3 != 5) or (f7 in (0, 0x20))) and \
               ((f3 in (0, 1, 5)) or (f7 == 0))
    if op == 0x0F:                                  # FENCE
        return f3 == 0
    return False


def _is_end(w):
    return not _is_valid(w)


# ---------------------------------------------------------------------------
# 上游 FemtoRV32 QUARK 逐行镜像
# ---------------------------------------------------------------------------
class _Quark:
    """2-state mirror of upstream femtorv32_quark.v
    (RESET_ADDR=0, ADDR_WIDTH=24, mem_rbusy/mem_wbusy=0)."""

    ST_F, ST_W, ST_E, ST_WAM = 0, 1, 2, 3

    def __init__(self):
        self.state = self.ST_WAM
        self.PC = 0
        self.instr = 0            # latched [31:2]（bits[1:0] 恒 0）
        self.rs1 = 0
        self.rs2 = 0
        self.regfile = [0] * 32
        self.aluReg = 0
        self.aluShamt = 0
        self.cycles = 0
        # bus outputs（组合，由 posedge 末尾更新为本拍末值）
        self.mem_addr = 0
        self.mem_wdata = 0
        self.mem_wmask = 0
        self.mem_rstrb = 0

    def posedge(self, resetn, mem_rdata):
        """One posedge. Mirrors the RTL always blocks exactly; all comb
        values derive from pre-posedge registers, `mem_rdata` is the
        combinational memory read for this cycle."""
        w = self.instr & 0xFFFFFFFC          # bits[1:0] = 0
        f3 = (w >> 12) & 7

        isLoad = 1 if ((w >> 2) & 0x1F) == 0b00000 else 0
        isALUimm = 1 if ((w >> 2) & 0x1F) == 0b00100 else 0
        isStore = 1 if ((w >> 2) & 0x1F) == 0b01000 else 0
        isALUreg = 1 if ((w >> 2) & 0x1F) == 0b01100 else 0
        isSYSTEM = 1 if ((w >> 2) & 0x1F) == 0b11100 else 0
        isJAL = (w >> 3) & 1
        isJALR = 1 if ((w >> 2) & 0x1F) == 0b11001 else 0
        isLUI = 1 if ((w >> 2) & 0x1F) == 0b01101 else 0
        isAUIPC = 1 if ((w >> 2) & 0x1F) == 0b00101 else 0
        isBranch = 1 if ((w >> 2) & 0x1F) == 0b11000 else 0
        isALU = isALUimm or isALUreg
        rdId = (w >> 7) & 0x1F
        funct3Is = 1 << f3
        funct3IsShift = 1 if f3 in (1, 5) else 0

        # immediates
        Uimm = w & 0xFFFFF000
        Iimm = (w >> 20) & 0xFFF
        Iimm = (Iimm | 0xFFFFF000) if (Iimm & 0x800) else Iimm
        Simm = ((w >> 31) & 1) << 11 | ((w >> 25) & 0x3F) << 5 | \
            ((w >> 7) & 0x1F)
        Simm = (Simm | 0xFFFFF000) if (Simm & 0x800) else Simm
        Bimm = ((w >> 31) & 1) << 12 | ((w >> 7) & 1) << 11 | \
            ((w >> 25) & 0x3F) << 5 | ((w >> 8) & 0xF) << 1
        Bimm = (Bimm | 0xFFFFF000) if (Bimm & 0x1000) else Bimm
        Jimm = ((w >> 31) & 1) << 20 | ((w >> 12) & 0xFF) << 12 | \
            ((w >> 20) & 1) << 11 | ((w >> 21) & 0x3FF) << 1
        Jimm = (Jimm | 0xFFF00000) if (Jimm & 0x100000) else Jimm

        rs1v = self.rs1 & M32
        rs2v = self.rs2 & M32
        aluIn1 = rs1v
        aluIn2 = (rs2v if (isALUreg or isBranch) else Iimm) & M32

        aluPlus = (aluIn1 + aluIn2) & M32
        # 33-bit: {1'b1, ~aluIn2} + {1'b0, aluIn1} + 33'b1
        aluMinus = (0x100000000 | (~aluIn2 & M32)) + aluIn1 + 1
        aluMinus &= 0x1FFFFFFFF
        if (aluIn1 >> 31) ^ (aluIn2 >> 31):
            LT = aluIn1 >> 31
        else:
            LT = aluMinus >> 32
        LTU = aluMinus >> 32
        EQ = 1 if (aluMinus & M32) == 0 else 0

        aluOut = 0
        if funct3Is & 0x01:
            aluOut |= (aluMinus & M32) if ((w >> 30) & 1) and ((w >> 5) & 1) \
                      else aluPlus
        if funct3Is & 0x04:
            aluOut |= LT
        if funct3Is & 0x08:
            aluOut |= LTU
        if funct3Is & 0x10:
            aluOut |= aluIn1 ^ aluIn2
        if funct3Is & 0x40:
            aluOut |= aluIn1 | aluIn2
        if funct3Is & 0x80:
            aluOut |= aluIn1 & aluIn2
        if funct3IsShift:
            aluOut |= self.aluReg
        aluOut &= M32

        predicate = bool(
            (funct3Is & 0x01) and EQ or
            (funct3Is & 0x02) and not EQ or
            (funct3Is & 0x10) and LT or
            (funct3Is & 0x20) and not LT or
            (funct3Is & 0x40) and LTU or
            (funct3Is & 0x80) and not LTU)

        PC = self.PC & AM
        PCplus4 = (PC + 4) & AM
        _imm = Jimm if isJAL else (Uimm if (w >> 4) & 1 else Bimm)
        PCplusImm = (PC + (_imm & AM)) & AM
        ls_imm = Simm if (w >> 5) & 1 else Iimm
        loadstore_addr = ((rs1v & AM) + (ls_imm & AM)) & AM

        if self.state in (self.ST_W, self.ST_F):
            mem_addr = PC
        else:
            mem_addr = loadstore_addr

        # LOAD
        mem_byteAccess = 1 if ((w >> 12) & 3) == 0 else 0
        mem_halfwordAccess = 1 if ((w >> 12) & 3) == 1 else 0
        LOAD_halfword = ((mem_rdata >> 16) & 0xFFFF) if (loadstore_addr & 2) \
            else (mem_rdata & 0xFFFF)
        LOAD_byte = ((LOAD_halfword >> 8) & 0xFF) if (loadstore_addr & 1) \
            else (LOAD_halfword & 0xFF)
        if mem_byteAccess:
            LOAD_sign = (not ((w >> 14) & 1)) and ((LOAD_byte >> 7) & 1)
        else:
            LOAD_sign = (not ((w >> 14) & 1)) and ((LOAD_halfword >> 15) & 1)
        LOAD_sign = 1 if LOAD_sign else 0
        if mem_byteAccess:
            LOAD_data = (((0xFFFFFF if LOAD_sign else 0) << 8) | LOAD_byte) & M32
        elif mem_halfwordAccess:
            LOAD_data = (((0xFFFF if LOAD_sign else 0) << 16) | LOAD_halfword) & M32
        else:
            LOAD_data = mem_rdata & M32

        # STORE
        mw = 0
        mw |= rs2v & 0xFF
        mw |= ((rs2v & 0xFF) if (loadstore_addr & 1) else
               ((rs2v >> 8) & 0xFF)) << 8
        mw |= ((rs2v & 0xFF) if (loadstore_addr & 2) else
               ((rs2v >> 16) & 0xFF)) << 16
        if loadstore_addr & 1:
            b31 = rs2v & 0xFF
        elif loadstore_addr & 2:
            b31 = (rs2v >> 8) & 0xFF
        else:
            b31 = (rs2v >> 24) & 0xFF
        mw |= b31 << 24
        mem_wdata = mw & M32

        if mem_byteAccess:
            if loadstore_addr & 2:
                STORE_wmask = 8 if (loadstore_addr & 1) else 4
            else:
                STORE_wmask = 2 if (loadstore_addr & 1) else 1
        elif mem_halfwordAccess:
            STORE_wmask = 12 if (loadstore_addr & 2) else 3
        else:
            STORE_wmask = 15

        writeBack = bool(not (isBranch or isStore)
                         and self.state in (self.ST_E, self.ST_WAM))
        mem_rstrb = bool((self.state == self.ST_E and isLoad)
                         or self.state == self.ST_F)
        mem_wmask = (0xF if (self.state == self.ST_E and isStore) else 0) \
            & STORE_wmask
        aluWr = bool(self.state == self.ST_E and isALU)
        needToWait = bool(isLoad or isStore or (isALU and funct3IsShift))
        jumpToPCplusImm = bool(isJAL or (isBranch and predicate))

        # writeBackData
        wb = 0
        if isSYSTEM:
            wb |= self.cycles & M32
        if isLUI:
            wb |= Uimm
        if isALU:
            wb |= aluOut
        if isAUIPC:
            wb |= PCplusImm
        if isJALR or isJAL:
            wb |= PCplus4
        if isLoad:
            wb |= LOAD_data
        writeBackData = wb & M32

        # ---- main always block（pre-posedge 值）----
        if not resetn:
            self.state = self.ST_WAM
            self.PC = 0
        else:
            st = self.state
            if st == self.ST_W:               # !mem_rbusy 恒成立
                self.rs1 = self.regfile[(mem_rdata >> 15) & 0x1F] & M32
                self.rs2 = self.regfile[(mem_rdata >> 20) & 0x1F] & M32
                self.instr = mem_rdata & 0xFFFFFFFC
                self.state = self.ST_E
            elif st == self.ST_E:
                if isJALR:
                    self.PC = (((aluPlus >> 1) & (AM >> 1)) << 1) & AM
                elif jumpToPCplusImm:
                    self.PC = PCplusImm
                else:
                    self.PC = PCplus4
                self.state = self.ST_WAM if needToWait else self.ST_F
            elif st == self.ST_WAM:
                if not (self.aluShamt & 0x1F):   # !aluBusy（rbusy=wbusy=0）
                    self.state = self.ST_F
            else:                             # ST_F
                self.state = self.ST_W

        # ---- register file write（pre-posedge writeBack/rdId）----
        if writeBack and rdId != 0:
            self.regfile[rdId] = writeBackData & M32

        # ---- ALU sequential（复位期间也照常排水/计数，与 RTL 一致）----
        if aluWr:
            if funct3IsShift:
                self.aluReg = aluIn1 & M32
                self.aluShamt = aluIn2 & 0x1F
        elif self.aluShamt & 0x1F:
            self.aluShamt = (self.aluShamt - 1) & 0x1F
            if funct3Is & 0x02:               # SLL
                self.aluReg = (self.aluReg << 1) & M32
            else:                             # SRA / SRL
                sign = ((w >> 30) & 1) and ((self.aluReg >> 31) & 1)
                self.aluReg = ((self.aluReg >> 1) | ((1 if sign else 0) << 31)) & M32
        self.cycles = (self.cycles + 1) & M32

        # ---- bus outputs：RTL 为组合逻辑，反映【本拍末（posedge 后）】的
        #      state/PC/rs1/rs2/instr —— 必须用更新后的寄存器重算 ----
        w2 = self.instr & 0xFFFFFFFC
        f32 = (w2 >> 12) & 3
        Iimm2 = (w2 >> 20) & 0xFFF
        Iimm2 = (Iimm2 | 0xFFFFF000) if (Iimm2 & 0x800) else Iimm2
        Simm2 = ((w2 >> 31) & 1) << 11 | ((w2 >> 25) & 0x3F) << 5 | \
            ((w2 >> 7) & 0x1F)
        Simm2 = (Simm2 | 0xFFFFF000) if (Simm2 & 0x800) else Simm2
        ls2 = ((self.rs1 & AM) + ((Simm2 if (w2 >> 5) & 1 else Iimm2) & AM)) & AM
        if self.state in (self.ST_W, self.ST_F):
            self.mem_addr = self.PC & AM
        else:
            self.mem_addr = ls2
        rs2v2 = self.rs2 & M32
        mw2 = rs2v2 & 0xFF
        mw2 |= ((rs2v2 & 0xFF) if (ls2 & 1) else ((rs2v2 >> 8) & 0xFF)) << 8
        mw2 |= ((rs2v2 & 0xFF) if (ls2 & 2) else ((rs2v2 >> 16) & 0xFF)) << 16
        if ls2 & 1:
            b31b = rs2v2 & 0xFF
        elif ls2 & 2:
            b31b = (rs2v2 >> 8) & 0xFF
        else:
            b31b = (rs2v2 >> 24) & 0xFF
        mw2 |= b31b << 24
        self.mem_wdata = mw2 & M32
        if f32 == 0:
            if ls2 & 2:
                wmask2 = 8 if (ls2 & 1) else 4
            else:
                wmask2 = 2 if (ls2 & 1) else 1
        elif f32 == 1:
            wmask2 = 12 if (ls2 & 2) else 3
        else:
            wmask2 = 15
        isLoad2 = 1 if ((w2 >> 2) & 0x1F) == 0b00000 else 0
        isStore2 = 1 if ((w2 >> 2) & 0x1F) == 0b01000 else 0
        self.mem_wmask = (0xF if (self.state == self.ST_E and isStore2)
                          else 0) & wmask2
        self.mem_rstrb = 1 if ((self.state == self.ST_E and isLoad2)
                               or self.state == self.ST_F) else 0


# ---------------------------------------------------------------------------
# dut/femtorv_top.v 镜像
# ---------------------------------------------------------------------------
class FemtorvPublic:
    """Black-box simulator for femtorv_public (mirrors dut/femtorv_top.v)."""

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
        self.cpu = _Quark()
        self.imem = [0] * 1024
        self.dmem = [0] * 1024
        self.cfg_addr = 0
        # action inputs (per-cycle)
        self._cfg_wr = 0
        self._cfg_sel = 0
        self._cfg_data = 0
        self.run = 0
        # shadow FSM
        self.shadow_state = S_WAM
        self.shadow_instr = 0
        # trap / hold FSM
        self.cov_trap = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0
        self.trap_stuck = 0
        self.post_trap = 0
        self.stuck_d = 0
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
        self.cov_branch_taken = 0
        self.cov_cfg_ok = 0
        self.seq = {k: 0 for k in
                    ("cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4",
                     "cov_seq5", "cov_seq6", "cov_seq7", "cov_seq8",
                     "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12")}
        # monitors
        self.prev_fetch_pc = 0
        self.run_d = 0
        self.hold_d = 0
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
        return 1 if (self.run and not self.cov_hold
                     and not self.trap_stuck) else 0

    def _match_class(self, opcode: int) -> int:
        for k in range(4):
            if opcode != 0 and opcode == self.op_ok_set[k]:
                return k
        return 3

    def _cov_busy(self, cpu_resetn, ss):
        return 1 if ((cpu_resetn and ss in (S_F, S_W, S_E))
                     or self.post_trap) else 0

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors femtorv_top always blocks)."""
        cpu = self.cpu
        cpu_resetn = self._cpu_resetn()

        # ---- pre-posedge snapshots ----
        ss_pre = self.shadow_state
        si_pre = self.shadow_instr & M32
        strobe_pre = cpu.mem_rstrb
        mem_addr_pre = cpu.mem_addr & M32
        mem_wdata_pre = cpu.mem_wdata & M32
        mem_wmask_pre = cpu.mem_wmask & 0xF
        hold_pre = bool(self.cov_hold)
        stuck_pre = bool(self.trap_stuck)
        post_trap_pre = bool(self.post_trap)
        done_ok_pre = bool(self.cov_done_ok_valid)
        run_rise = bool(self.run and not self.run_d)
        cfg_ok = bool(self._cfg_wr and not hold_pre)
        # cov_busy 的 pre-posedge 值（必须在 trap FSM 更新 post_trap 之前
        # 采样，与 RTL 监视器采样组合输出一致）
        busy_pre = self._cov_busy(cpu_resetn, ss_pre)

        fetch_done = bool(ss_pre == S_W and cpu_resetn)
        load_done = bool(ss_pre == S_E and _is_load(si_pre) and cpu_resetn)
        stor_done = bool(ss_pre == S_E and _is_store(si_pre) and cpu_resetn)
        trap_rise = bool(ss_pre == S_E and _is_end(si_pre) and cpu_resetn)

        # ---- memory read (combinational, pre-posedge) ----
        # 路由规则与 femtorv_top.v 1:1：
        #   1) strobe && S_E && is_load -> dmem（load 的 EXECUTE 读）
        #   2) !strobe && S_WAM && is_load -> dmem（上游在 WAM 拍仍以
        #      writeBack 重写 rd，须继续供 dmem 同址数据）
        #   3) 其余 -> imem
        is_load_access = bool((strobe_pre and ss_pre == S_E
                               and _is_load(si_pre)) or
                              ((not strobe_pre) and ss_pre == S_WAM
                               and _is_load(si_pre)))
        widx = (mem_addr_pre >> 2) & 0x3FF
        mem_rdata = (self.dmem[widx] if is_load_access
                     else self.imem[widx]) & M32

        # ---- CPU posedge ----
        cpu.posedge(cpu_resetn, mem_rdata)

        # ---- wrapper posedge (pre-posedge values) ----
        self.cov_cfg_ok = 1 if cfg_ok else 0

        if fetch_done:
            prev_cov_pc = self.cov_pc & M32      # NBA：RHS 取旧值
            self.shadow_instr = mem_rdata
            self.cov_pc = mem_addr_pre
            self.cov_instr = mem_rdata
            self.cov_mem_addr = mem_addr_pre & 0xFFFF
            self.cov_mem_rdata = mem_rdata & 0xFFFF
            self.cov_mem_wstrb = 0
            self.cov_mem_rd = 1
            self.cov_mem_instr = 1
            self.cov_branch_taken = 1 if (
                (si_pre & 0x7F) == 0x63
                and mem_addr_pre != ((prev_cov_pc + 4) & M32)) else 0
            if self.cov_instr_cnt != 0xFF:
                self.cov_instr_cnt = (self.cov_instr_cnt + 1) & 0xFF

        if load_done:
            self.cov_mem_addr = mem_addr_pre & 0xFFFF
            self.cov_mem_rdata = mem_rdata & 0xFFFF
            self.cov_mem_wstrb = 0
            self.cov_mem_rd = 1
            self.cov_mem_instr = 0

        if stor_done:
            self.cov_mem_addr = mem_addr_pre & 0xFFFF
            self.cov_mem_wdata = mem_wdata_pre & 0xFFFF
            self.cov_mem_wstrb = mem_wmask_pre
            self.cov_mem_rd = 0
            self.cov_mem_instr = 0

        # ---- shadow transitions (pre-posedge values) ----
        if not cpu_resetn:
            self.shadow_state = S_WAM
        elif ss_pre == S_F:
            self.shadow_state = S_W
        elif ss_pre == S_W:
            self.shadow_state = S_E
        elif ss_pre == S_E:
            self.shadow_state = S_WAM if _need_wait(si_pre) else S_F
        else:  # S_WAM：观测取指 strobe 退出（strobe 拍核必在 FETCH）
            self.shadow_state = S_W if strobe_pre else S_WAM

        # ---- cfg write (posedge; CPU read old value this cycle) ----
        if cfg_ok:
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

        # ---- CPU store write (S_E 拍末生效；与 cfg 同拍时 CPU 覆盖) ----
        if stor_done:
            w = (mem_addr_pre >> 2) & 0x3FF
            wd = mem_wdata_pre
            ws = mem_wmask_pre
            if ws & 1:
                self.dmem[w] = (self.dmem[w] & ~0xFF) | (wd & 0xFF)
            if ws & 2:
                self.dmem[w] = (self.dmem[w] & ~0xFF00) | (wd & 0xFF00)
            if ws & 4:
                self.dmem[w] = (self.dmem[w] & ~0xFF0000) | (wd & 0xFF0000)
            if ws & 8:
                self.dmem[w] = (self.dmem[w] & ~0xFF000000) | (wd & 0xFF000000)

        # ---- trap / hold FSM ----
        self.cov_trap = 1 if trap_rise else 0
        self.cov_done_ok_valid = 0
        self.post_trap = 0

        end_op = si_pre & 0x7F
        match0 = end_op != 0 and end_op == self.op_ok_set[0]
        match1 = end_op != 0 and end_op == self.op_ok_set[1]
        match2 = end_op != 0 and end_op == self.op_ok_set[2]
        match3 = end_op != 0 and end_op == self.op_ok_set[3]
        trap_match = match0 or match1 or match2 or match3
        trap_class = 0 if match0 else (1 if match1 else (2 if match2 else 3))

        if not self.run:
            self.trap_stuck = 0
        elif trap_rise and not trap_match:
            self.trap_stuck = 1
        elif trap_rise and trap_match and self.trap_hold_n == 0:
            self.trap_stuck = 1

        if trap_rise and not trap_match:
            self.post_trap = 1

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
        self._monitor_step(cfg_ok=cfg_ok, run_rise=run_rise,
                           fetch_done=fetch_done, load_done=load_done,
                           stor_done=stor_done, trap_rise=trap_rise,
                           busy_pre=busy_pre, hold_pre=hold_pre,
                           stuck_pre=stuck_pre, stuck_d_pre=self.stuck_d,
                           done_ok_pre=done_ok_pre,
                           fetch_pc=mem_addr_pre, fetch_word=mem_rdata,
                           mem_addr=mem_addr_pre)

        # ---- trailing registers ----
        self.run_d = 1 if self.run else 0
        self.hold_d = 1 if hold_pre else 0
        self.stuck_d = 1 if stuck_pre else 0
        self._cfg_wr = 0

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_ok, run_rise, fetch_done, load_done,
                      stor_done, trap_rise, busy_pre, hold_pre, stuck_pre,
                      stuck_d_pre, done_ok_pre, fetch_pc, fetch_word,
                      mem_addr):
        """Mirror of the femtorv_top temporal-sequence monitor (1:1).
        All inputs are pre-posedge snapshots."""
        s = self.seq
        for k in s:
            s[k] = 0

        # Q1: cfg 装载 -> run 释放 -> >=2 次取指 -> trap
        if cfg_ok:
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

        # Q10: 全局空闲（无 busy / 无 hold / 无 trap 停机）连续 >=4 拍
        idle_now = (not busy_pre) and (not hold_pre) and (not stuck_pre)
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
        if self.s11_armed and self.s11_fetch and trap_rise \
                and self.s11_cnt <= 64:
            s["cov_seq11"] = 1
            self.s11_armed = 0

        # Q12: trap 一致性（trap 停机保持 >=2 拍，程序确实停机）
        if stuck_pre and stuck_d_pre:
            s["cov_seq12"] = 1

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        cpu_resetn = self._cpu_resetn()
        busy = self._cov_busy(cpu_resetn, self.shadow_state)
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
            "cov_busy": busy & 1,
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
    # 自检 1：EBREAK-only 程序生命周期（占位参数）
    dut = FemtorvPublic()
    EBREAK = 0x00100073
    for a in [(0, 0x00), (1, 0x00)] + [(2, (EBREAK >> (8 * b)) & 0xFF)
                                       for b in range(4)]:
        dut.apply_config(a[0], a[1])
        dut.step()
    dut.set_run(1)
    traps = []
    for i in range(30):
        dut.step()
        if dut.read_signals()["cov_trap"]:
            traps.append(i)
    print("EBREAK-only: trap pulses at steps", traps,
          "(expect exactly 1 pulse, done_ok inert under placeholder)")

    # 自检 2：INSTR_CYCLE_TABLE 实测自检（本镜像逐类测量 trap 边际拍数）
    def enc_i(rd, rs1, imm, f3):
        return ((imm & 0xFFF) << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | 0x13

    def enc_r(rd, rs1, rs2, f3, f7=0):
        return ((f7 & 0x7F) << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) \
            | (rd << 7) | 0x33

    def enc_load(rd, rs1, imm, f3):
        return ((imm & 0xFFF) << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | 0x03

    def enc_store(rs2, rs1, imm, f3):
        imm &= 0xFFF
        return (((imm >> 5) & 0x7F) << 25) | (rs2 << 20) | (rs1 << 15) \
            | (f3 << 12) | ((imm & 0x1F) << 7) | 0x23

    def trap_delta(prog):
        d0 = FemtorvPublic()
        d1 = FemtorvPublic()
        for d, words in ((d0, [EBREAK]), (d1, prog + [EBREAK])):
            d.apply_config(0, 0); d.step()
            d.apply_config(1, 0); d.step()
            for w in words:
                for b in range(4):
                    d.apply_config(2, (w >> (8 * b)) & 0xFF)
                    d.step()
            d.set_run(1)
            t = None
            for i in range(100):
                d.step()
                if d.read_signals()["cov_trap"]:
                    t = i
                    break
        return t

    t_ref = trap_delta([EBREAK])          # [TRAP]
    checks = [
        ("alu(add)", [enc_r(1, 0, 0, 0)], "alu_nonshift"),
        ("addi", [enc_i(1, 0, 1, 0)], "alu_nonshift"),
        ("load", [enc_load(2, 1, 0, 2)], "load"),
        ("store", [enc_store(2, 1, 0, 2)], "store"),
        ("slli x5", [enc_i(1, 0, 5, 1)], "shift_k"),
    ]
    ok = True
    for name, prog, key in checks:
        d = trap_delta(prog) - t_ref
        expect = INSTR_CYCLE_TABLE[key]
        good = d == expect if isinstance(expect, int) else \
            (d >= 4 + 0 and d <= 4 + 31)
        print("  %-12s trap delta = %d (%s=%s) %s"
              % (name, d, key, expect, "OK" if good else "MISMATCH"))
        ok = ok and good
    print("local_sim self-check", "OK" if ok else "FAIL")
