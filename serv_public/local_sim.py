#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
serv_public - Black-box simulator (local_sim.py).
Python mirror of dut/serv_top.v (upstream olofk/serv SERV bit-serial RV32I CPU,
ISC) for local development and evaluation. The mirror reproduces the RTL
cycle-accurately at the cov_* observation level.

Model structure (per dut/dut_spec.md §3):
  - Python model = 功能级 RV32I 执行（serv 精确解码）+ Verilator 4.038 实测
    周期表驱动 cov 节拍（picorv32_public 同法）。位串行 CPU 的逐位状态机不
    逐拍复刻，而是以"取指完成事件"为节拍：每条指令的取指完成→下一条取指
    完成的拍数 T_class 与 dbus 访问偏移（+36 拍）由实测表给出（Verilator
    实测，cross_check.py 与 RTL 对拍验证）。
  - cov_busy = CPU 释放电平（释放期间取指/执行/访问连续覆盖，无空闲隙）；
    trap 检测 = 上游 e_op 解码 + load/store 无 dbus + 分支目标算术（2 深取指
    历史回填"结束指令"），与 dut/serv_top.v 1:1。
  - 隐藏参数（op_ok_set, trap_hold_n）外部注入；公开占位 OP_OK_SET=[0,0,0,0]
    （槽位值 0 永不匹配 → done_ok 惰性）、TRAP_HOLD_N=16。
  - 契约：run 拉低仅用于装载阶段与 trap 驻留后的重启；指令执行中途复位为
    未定义行为（RTL 位串行寄存器堆会产生部分位回写，模型按原子语义处理，
    契约内不会出现）。

实测周期表（Verilator 4.038，[INSTR; EBREAK] 与 [EBREAK] 边际差，单位拍，
取指完成→下一条取指完成）：
  R/I 单拍类（ADD/SUB/XOR/OR/AND/ADDI/XORI/ORI/ANDI/LUI/AUIPC）: 36
  R/I 双拍类（SLT/SLTU/SLL/SRL/SRA/SLTI/SLTIU/SLLI）          : 68
  右移（SRL/SRA = 68 + rs2[4:0]；SRLI/SRAI = 68 + shamt）      : 68+N
  分支（taken/not-taken）/ JAL / JALR                          : 68
  load / store（dbus ack 在取指完成 +36 拍）                    : 70
  FENCE（serv 解码为 U 型 + 1 次 dbus 字节读，建议 rd=x0）       : 70
  EBREAK/ECALL/custom-3（e_op，单拍）                          : 36
  非对齐 load/store（无 dbus）                                 : 70
  非对齐分支 / JAL / JALR（PC→mtvec=0）                        : 70

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

# ---- 实测周期表（Verilator 4.038，见 dut_spec.md §3.2）----
T_SINGLE = 36        # 单拍执行类
T_TWO = 68           # 双拍执行类（不含右移/MEM/分支异常）
T_MEM = 70           # load/store/fence + 非对齐异常类
DBUS_OFF = 36        # dbus ack 相对取指完成的偏移（拍）
T_TRAP_JUMP = 70     # 非对齐分支/JAL/JALR（PC→mtvec，本包不产生 trap 事件）


def _sx(v, bits):
    """sign-extend a two's complement value of `bits` width."""
    s = 1 << (bits - 1)
    m = (1 << bits) - 1
    v &= m
    return v - 2 * s if v & s else v


def _imm_i(w):
    return _sx(w >> 20, 12) & M32


def _imm_s(w):
    return _sx(((w >> 25) << 5) | ((w >> 7) & 0x1F), 12) & M32


def _imm_b(w):
    return _sx(((w >> 31) & 1) << 12 | ((w >> 7) & 1) << 11
               | ((w >> 25) & 0x3F) << 5 | ((w >> 8) & 0xF) << 1, 13) & M32


def _imm_j(w):
    v = w >> 12
    out = (((v >> 19) & 1) << 20) | (((v >> 9) & 0x3FF) << 1) | \
          (((v >> 8) & 1) << 11) | ((v & 0xFF) << 12)
    return _sx(out, 21) & M32


def _imm_u(w):
    return (w & 0xFFFFF000) & M32


class _ServCpu:
    """Functional RV32I core (serv-exact decode for the contract subset).

    Executes one instruction per call. The timing (T_class / dbus offset)
    is applied by the surrounding ServPublic event scheduler.
    """

    def __init__(self):
        self.regs = [0] * 32
        self.mepc = 0       # 每次 trap 写入；mret 跳转目标
        self.mtvec = 0      # 契约：恒为 0（程序不得改写 mtvec）

    def execute(self, w, pc):
        """Execute instruction w at pc. Returns a dict:

        next_pc  : 下一条取指地址（trap → mtvec）
        t_class  : 取指完成→下一条取指完成的拍数
        dbus     : None 或 (word_idx, sel, we)
        store    : None 或 (word_idx, do_store(mem)) 提交函数
        rd_wr    : (rd, value) 立即回写（ALU/JAL/JALR/LUI/AUIPC/FENCE）
        load_rd  : (rd, f3, lsb) load 回写描述（数据在 dbus 事件拍取）
        """
        w &= M32
        op5 = (w >> 2) & 0x1F
        f3 = (w >> 12) & 7
        rd = (w >> 7) & 0x1F
        rs1 = (w >> 15) & 0x1F
        rs2 = (w >> 20) & 0x1F
        regs = self.regs
        r1 = regs[rs1] & M32
        r2 = regs[rs2] & M32

        e_op = 1 if (w & 0x40) and (w & 0x10) and not (w & 0x200000) and f3 == 0 else 0
        mret = 1 if (w & 0x40) and (w & 0x10) and (w & 0x200000) and f3 == 0 else 0
        word_a = f3 & 2
        half_a = f3 & 1

        def misalign(a):
            return 1 if ((a & 1) and (word_a or half_a)) \
                or ((a & 2) and word_a) else 0

        def bus_sel(a):
            lsb = a & 3
            sel3 = 1 if (lsb == 3) or word_a or (half_a and (lsb >> 1)) else 0
            sel2 = 1 if (lsb == 2) or word_a else 0
            sel1 = 1 if (lsb == 1) or word_a or (half_a and not (lsb >> 1)) else 0
            sel0 = 1 if (lsb == 0) else 0
            return (sel3 << 3) | (sel2 << 2) | (sel1 << 1) | sel0

        def ret(**kw):
            d = {"next_pc": (pc + 4) & M32, "t_class": T_SINGLE, "dbus": None,
                 "store": None, "rd_wr": None, "load_rd": None}
            d.update(kw)
            return d

        # -------------------------------------------------- SYSTEM / custom-3
        if op5 in (0b11100, 0b11110):
            if e_op:
                self.mepc = pc & M32
                return ret(next_pc=self.mtvec & M32, t_class=T_SINGLE)
            if mret:
                return ret(next_pc=self.mepc & M32, t_class=T_SINGLE)
            # CSR 访问（契约外；本地模型 rd=0 占位，测试程序不使用）
            return ret(rd_wr=(rd, 0))

        # -------------------------------------------------- BRANCH / JAL / JALR
        if op5 == 0b11000:  # branch
            eq = 1 if r1 == r2 else 0
            lts = 1 if _sx(r1, 32) < _sx(r2, 32) else 0
            ltu = 1 if r1 < r2 else 0
            take = 0
            if f3 == 0:
                take = eq
            elif f3 == 1:
                take = 1 - eq
            elif f3 == 4:
                take = lts
            elif f3 == 5:
                take = 1 - lts
            elif f3 == 6:
                take = ltu
            elif f3 == 7:
                take = 1 - ltu
            if take:
                tgt = (pc + _imm_b(w)) & M32
                if tgt & 2:  # 非对齐跳转（ALIGN=0 上游 trap；非 DUT trap 事件）
                    return ret(next_pc=self.mtvec & M32, t_class=T_TRAP_JUMP)
                return ret(next_pc=tgt & ~1 & M32, t_class=T_TWO)
            return ret(t_class=T_TWO)

        if op5 == 0b11011:  # jal
            tgt = (pc + _imm_j(w)) & M32
            if tgt & 2:
                return ret(next_pc=self.mtvec & M32, t_class=T_TRAP_JUMP)
            return ret(next_pc=tgt & ~1 & M32, t_class=T_TWO,
                       rd_wr=(rd, (pc + 4) & M32))

        if op5 == 0b11001:  # jalr
            tgt = (r1 + _imm_i(w)) & M32
            if tgt & 2:
                return ret(next_pc=self.mtvec & M32, t_class=T_TRAP_JUMP)
            return ret(next_pc=tgt & ~1 & M32, t_class=T_TWO,
                       rd_wr=(rd, (pc + 4) & M32))

        # -------------------------------------------------- LOAD / STORE / FENCE
        if op5 == 0b01000:  # store
            addr = (r1 + _imm_s(w)) & M32
            if misalign(addr):
                self.mepc = pc & M32
                return ret(next_pc=self.mtvec & M32, t_class=T_MEM)
            word_i = (addr >> 2) & 0x3FF
            sel = bus_sel(addr)
            lsb = addr & 3

            def do_store(mem):
                wd = mem[word_i]
                if f3 == 0:                       # sb
                    lane = 0xFF << (8 * lsb)
                    mem[word_i] = (wd & ~lane) | ((r2 & 0xFF) << (8 * lsb))
                elif f3 == 1:                     # sh
                    lane = 0xFFFF << (8 * (lsb & 2))
                    mem[word_i] = (wd & ~lane) | ((r2 & 0xFFFF) << (8 * (lsb & 2)))
                else:                             # sw（f3=2；3/6/7 契约外近似整字）
                    mem[word_i] = r2 & M32
            return ret(t_class=T_MEM, dbus=(word_i, (addr & ~3) & 0xFFFF, sel, 1),
                       store=(word_i, do_store))

        if op5 == 0b00000:  # load（opcode 0x00..0x03：w[6:2]=0b00000，含 custom-0）
            addr = (r1 + _imm_i(w)) & M32
            if misalign(addr):
                self.mepc = pc & M32
                return ret(next_pc=self.mtvec & M32, t_class=T_MEM)
            return ret(t_class=T_MEM, dbus=((addr >> 2) & 0x3FF,
                                            (addr & ~3) & 0xFFFF, bus_sel(addr), 0),
                       load_rd=(rd, f3, addr & 3))

        if op5 == 0b00011:  # fence（serv 解码为 U 型 + dbus 字节读；建议 rd=x0）
            addr = (r1 + _imm_i(w)) & M32
            return ret(t_class=T_MEM, dbus=((addr >> 2) & 0x3FF,
                                            (addr & ~3) & 0xFFFF, bus_sel(addr), 0),
                       rd_wr=(rd, pc & M32))

        # -------------------------------------------------- LUI / AUIPC
        if op5 == 0b01101:  # lui
            return ret(rd_wr=(rd, _imm_u(w)))

        if op5 == 0b00101:  # auipc
            return ret(rd_wr=(rd, (pc + _imm_u(w)) & M32))

        # -------------------------------------------------- OP / OP-IMM
        is_op = 1 if op5 == 0b01100 else 0
        shamt = (w >> 20) & 0x1F if not is_op else (r2 & 0x1F)
        two_stage = 0
        if f3 == 0:
            out = (r1 - r2) & M32 if (w & 0x40000000) else (r1 + r2) & M32
        elif f3 == 1:
            out = (r1 << shamt) & M32
            two_stage = 1
        elif f3 == 2:
            out = 1 if _sx(r1, 32) < _sx(r2, 32) else 0
            two_stage = 1
        elif f3 == 3:
            out = 1 if r1 < r2 else 0
            two_stage = 1
        elif f3 == 4:
            out = r1 ^ r2
        elif f3 == 5:
            if w & 0x40000000:
                v = r1 if not (r1 & 0x80000000) else r1 | 0x100000000
                out = (v >> shamt) & M32
            else:
                out = (r1 >> shamt) & M32
            two_stage = 1
        elif f3 == 6:
            out = r1 | r2
        else:
            out = r1 & r2
        if not is_op:  # op-imm：rs2 → imm
            imm = _imm_i(w)
            if f3 == 0:
                out = (r1 + imm) & M32
            elif f3 == 2:
                out = 1 if _sx(r1, 32) < _sx(imm, 32) else 0
            elif f3 == 3:
                out = 1 if r1 < (imm & M32) else 0
            elif f3 == 4:
                out = r1 ^ imm
            elif f3 == 6:
                out = r1 | imm
            elif f3 == 7:
                out = r1 & imm
            elif f3 == 1:
                out = (r1 << shamt) & M32
            elif f3 == 5:
                if w & 0x40000000:
                    v = r1 if not (r1 & 0x80000000) else r1 | 0x100000000
                    out = (v >> shamt) & M32
                else:
                    out = (r1 >> shamt) & M32
        t = T_TWO + shamt if (two_stage and f3 == 5) else \
            (T_TWO if two_stage else T_SINGLE)
        return ret(t_class=t, rd_wr=(rd, out & M32))


class ServPublic:
    """Black-box simulator for serv_public (mirrors dut/serv_top.v)."""

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
        self.cpu = _ServCpu()
        self.imem = [0] * 1024
        self.dmem = [0] * 1024
        self.cfg_addr = 0
        self._cfg_wr = 0
        self._cfg_sel = 0
        self._cfg_data = 0
        self.run = 0
        # 事件调度
        self.t = 0
        self.pc = 0
        self._cpu_resetn_prev = 0
        self._fetch_at = None
        self._dbus_at = None
        self._dbus_pend = None     # (word_idx, sel, we, load_rd)
        self._dbus_rdata_pre = 0   # dbus 拍前 1 拍锁存的 dmem 整字（提交前）
        self._st_at = None         # store 提交拍（dbus 首拍 posedge）
        self._st_pend = None       # (word_idx, do_store)
        # 取指历史 / trap 上下文
        self.hist0_pc = 0
        self.hist0_insn = 0
        self.hist1_pc = 0
        self.hist1_insn = 0
        self.hist0_valid = 0
        self.dbus_seen = 0
        # 隐藏机制
        self.trap_lat = 0
        self.stuck = 0
        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0
        # cov 寄存器
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
        # 监视器
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
        self.s12_cnt = 0

    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        self._cfg_wr = 1
        self._cfg_sel = int(sel) & 7
        self._cfg_data = int(data) & 0xFF

    def set_run(self, run: int):
        self.run = 1 if int(run) & 1 else 0

    # ------------------------------------------------------------------
    def _cpu_resetn(self):
        return 1 if (self.run and not self.cov_hold and not self.stuck) else 0

    def _is_eop(self, w):
        w &= M32
        return 1 if (w & 0x40) and (w & 0x10) and not (w & 0x200000) \
            and ((w >> 12) & 7) == 0 else 0

    def _cancel_events(self):
        self._fetch_at = None
        self._dbus_at = None
        self._dbus_pend = None
        self._st_at = None
        self._st_pend = None

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors serv_top always blocks)."""
        self.t += 1
        cpu_resetn_pre = self._cpu_resetn()

        # ---- pre-posedge snapshots ----
        cfg_evt = bool(self._cfg_wr and not self.cov_hold)
        run_rise = bool(self.run and not self.run_d)
        fetch_done = bool(cpu_resetn_pre and self._fetch_at == self.t)
        dbus_done = bool(cpu_resetn_pre and self._dbus_at == self.t)
        st_commit = bool(cpu_resetn_pre and self._st_at == self.t)
        hold_pre = bool(self.cov_hold)
        done_ok_pre = bool(self.cov_done_ok_valid)
        stuck_pre = bool(self.stuck)

        fetch_pc = (self.pc & M32) if fetch_done else 0
        fetch_word = (self.imem[(self.pc >> 2) & 0x3FF] & M32) if fetch_done else 0
        dbus_we_evt = 0
        dbus_addr16_evt = 0
        if dbus_done and self._dbus_pend is not None:
            dbus_we_evt = self._dbus_pend[3]
            dbus_addr16_evt = self._dbus_pend[1]

        # ---- dbus 前 1 拍：锁存提交前的 dmem 整字（rdt_q 采样拍，先于 cfg/
        #      存储提交）----
        if cpu_resetn_pre and self._dbus_at == self.t + 1 \
                and self._dbus_pend is not None:
            self._dbus_rdata_pre = self.dmem[self._dbus_pend[0]] & M32

        # ---- trap 检测（预 posedge 组合，与 serv_top 1:1）----
        hist0_insn_pre = self.hist0_insn & M32
        hist0_pc_pre = self.hist0_pc & M32
        eop_hist0 = self._is_eop(hist0_insn_pre)
        ldst_hist0 = 1 if (hist0_insn_pre & 0x7F) in (0x03, 0x23) else 0
        br_hist0 = 1 if (hist0_insn_pre & 0x7F) == 0x63 else 0
        bimm_hist0 = _imm_b(hist0_insn_pre)
        br_mis_trap = bool(br_hist0 and fetch_done
                           and (fetch_pc != ((hist0_pc_pre + 4) & M32))
                           and (fetch_pc != ((hist0_pc_pre + bimm_hist0) & M32)))
        ldst_mis_trap = bool(ldst_hist0 and not self.dbus_seen)
        trap_evt = bool(fetch_done and not self.trap_lat and self.hist0_valid
                        and (eop_hist0 or ldst_mis_trap or br_mis_trap))

        # ---- cov 寄存器（与 serv_top 顺序一致：取指 → dbus → cfg → 存储提交
        #      → trap 回填）----
        self.cov_cfg_ok = 1 if cfg_evt else 0
        if fetch_done:
            self.hist1_pc = self.hist0_pc
            self.hist1_insn = self.hist0_insn
            self.hist0_pc = fetch_pc
            self.hist0_insn = fetch_word
            self.hist0_valid = 1
            self.dbus_seen = 0
            prev_op = self.cov_instr & 0x7F
            prev_pc = self.cov_pc & M32
            self.cov_pc = fetch_pc
            self.cov_instr = fetch_word
            self.cov_mem_addr = fetch_pc & 0xFFFF
            self.cov_mem_rdata = fetch_word & 0xFFFF
            self.cov_mem_wstrb = 0
            self.cov_mem_rd = 1
            self.cov_mem_instr = 1
            self.cov_branch_taken = 1 if (
                prev_op == 0x63 and fetch_pc != ((prev_pc + 4) & M32)) else 0
            if self.cov_instr_cnt != 0xFF:
                self.cov_instr_cnt = (self.cov_instr_cnt + 1) & 0xFF
        if dbus_done and self._dbus_pend is not None:
            (widx, dadr16, sel, we, load_rd) = self._dbus_pend
            self.cov_mem_addr = dadr16 & 0xFFFF
            self.cov_mem_rdata = self._dbus_rdata_pre & 0xFFFF
            self.cov_mem_wstrb = sel & 0xF
            self.cov_mem_rd = 0 if we else 1
            self.cov_mem_instr = 0
            self.cov_mem_wdata = self.dmem[widx] & 0xFFFF   # 提交后整字
            if load_rd is not None:
                rd, f3, lsb = load_rd
                wd = self._dbus_rdata_pre & M32
                if f3 == 0:
                    v = _sx((wd >> (8 * lsb)) & 0xFF, 8)
                elif f3 == 1:
                    v = _sx((wd >> (8 * (lsb & 2))) & 0xFFFF, 16)
                elif f3 == 4:
                    v = (wd >> (8 * lsb)) & 0xFF
                elif f3 == 5:
                    v = (wd >> (8 * (lsb & 2))) & 0xFFFF
                else:
                    v = wd
                if rd:
                    self.cpu.regs[rd] = v & M32
            self._dbus_pend = None
            self._dbus_at = None
        # cfg 写（posedge 生效；CPU 本拍读旧值）
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
                    self.dmem[w] = (self.dmem[w] & ~(0xFF << (8 * lane))) \
                        | (self._cfg_data << (8 * lane))
                else:
                    self.imem[w] = (self.imem[w] & ~(0xFF << (8 * lane))) \
                        | (self._cfg_data << (8 * lane))
                self.cfg_addr = (self.cfg_addr + 1) & 0xFFFF
        # CPU 存储提交（dbus 首拍 posedge；同拍冲突覆盖 cfg 写）
        if st_commit and self._st_pend is not None:
            widx, do_store = self._st_pend
            do_store(self.dmem)
            self._st_pend = None
            self._st_at = None
        # trap 上升沿：回填"结束指令"（预 posedge 取指历史 = 触发 trap 的指令）
        if trap_evt:
            self.cov_instr = hist0_insn_pre
            self.cov_pc = hist0_pc_pre

        # ---- 取指历史 dbus 标记（复位/挂起期间失效）----
        if not cpu_resetn_pre:
            self.hist0_valid = 0
            self.dbus_seen = 0
        elif dbus_done:
            self.dbus_seen = 1

        # ---- trap / hold / stuck FSM ----
        self.cov_trap = 1 if trap_evt else 0
        self.cov_done_ok_valid = 0
        end_op = hist0_insn_pre & 0x7F
        m0 = end_op != 0 and end_op == self.op_ok_set[0]
        m1 = end_op != 0 and end_op == self.op_ok_set[1]
        m2 = end_op != 0 and end_op == self.op_ok_set[2]
        m3 = end_op != 0 and end_op == self.op_ok_set[3]
        trap_match = m0 or m1 or m2 or m3
        trap_class = 0 if m0 else (1 if m1 else (2 if m2 else 3))
        if not self.run:
            self.trap_lat = 0
            self.stuck = 0
        if trap_evt:
            self.trap_lat = 1
        if self.hld_state == 0:
            if trap_evt and trap_match:
                if self.trap_hold_n == 0:
                    self.cov_done_ok_valid = 1
                    self.cov_done_ok_class = trap_class
                    self.stuck = 1
                else:
                    self.hld_state = 1
                    self.hld_cnt = self.trap_hold_n & 0xFFFF
                    self.hld_class = trap_class
                    self.cov_hold = 1
            elif trap_evt:
                self.stuck = 1
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

        # ---- 调度：cpu_resetn 上升沿 → 取指事件（R+1）；下降沿取消 ----
        cpu_resetn_now = self._cpu_resetn()
        rise = bool(cpu_resetn_pre and not self._cpu_resetn_prev)
        drop = bool((not cpu_resetn_pre) and self._cpu_resetn_prev)
        if drop:
            self._cancel_events()
        if rise:
            self._fetch_at = self.t + 1

        # ---- 功能执行（取指完成拍：推进 PC、调度下一条取指/dbus/store）----
        if fetch_done and cpu_resetn_now:
            res = self.cpu.execute(fetch_word, fetch_pc)
            self.pc = res["next_pc"] & M32
            self._fetch_at = self.t + res["t_class"]
            if res["rd_wr"] is not None:
                rdw, val = res["rd_wr"]
                if rdw:
                    self.cpu.regs[rdw] = val & M32
            if res["store"] is not None:
                widx, do_store = res["store"]
                self._st_at = self.t + DBUS_OFF - 1
                self._st_pend = (widx, do_store)
            if res["dbus"] is not None:
                widx, dadr16, sel, we = res["dbus"]
                self._dbus_at = self.t + DBUS_OFF
                self._dbus_pend = (widx, dadr16, sel, we, res["load_rd"])
        # 取指完成后 busy 连续：cov_busy ≡ cpu_resetn（见 docstring）

        # ---- monitors（pre-posedge 快照，与 serv_top 1:1）----
        self._monitor_step(cfg_evt=cfg_evt, run_rise=run_rise,
                           fetch_done=fetch_done, dbus_done=dbus_done,
                           dbus_we=dbus_we_evt,
                           trap_evt=trap_evt, busy_pre=cpu_resetn_pre,
                           hold_pre=hold_pre, done_ok_pre=done_ok_pre,
                           stuck_pre=stuck_pre,
                           fetch_pc=fetch_pc, fetch_word=fetch_word,
                           dbus_addr16=dbus_addr16_evt)

        # ---- trailing registers ----
        self.run_d = 1 if self.run else 0
        self.hold_d = 1 if hold_pre else 0
        self._cfg_wr = 0
        self._cpu_resetn_prev = cpu_resetn_now

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_evt, run_rise, fetch_done, dbus_done, dbus_we,
                      trap_evt, busy_pre, hold_pre, done_ok_pre, stuck_pre,
                      fetch_pc, fetch_word, dbus_addr16):
        """Mirror of the serv_top temporal-sequence monitor (1:1).
        All inputs are pre-posedge snapshots; 状态一律按预 posedge 值读取、
        posedge 后统一更新（与 RTL 非阻塞赋值语义一致）。"""
        s = self.seq
        for k in s:
            s[k] = 0
        # pre-posedge state
        s1_cfg, s1_run, s1_cnt = self.s1_cfg, self.s1_run, self.s1_cnt
        s2_back = self.s2_back
        s3_fwd = self.s3_fwd
        s4_state, s4_addr = self.s4_state, self.s4_addr
        s5_streak = self.s5_streak
        s6_cnt = self.s6_cnt
        s8_cnt = self.s8_cnt
        s9_armed = self.s9_armed
        s10_cnt = self.s10_cnt
        s11_armed, s11_cnt, s11_fetch = self.s11_armed, self.s11_cnt, self.s11_fetch
        s12_cnt = self.s12_cnt
        prev_fetch_pc = self.prev_fetch_pc

        # ---- 新值（默认保持，逐项覆盖）----
        n_s1_cfg, n_s1_run, n_s1_cnt = s1_cfg, s1_run, s1_cnt
        n_s2_back = s2_back
        n_s3_fwd = s3_fwd
        n_s4_state, n_s4_addr = s4_state, s4_addr
        n_s5_streak = s5_streak
        n_s6_cnt = s6_cnt
        n_s8_cnt = s8_cnt
        n_s9_armed = s9_armed
        n_s10_cnt = s10_cnt
        n_s11_armed, n_s11_cnt, n_s11_fetch = s11_armed, s11_cnt, s11_fetch
        n_s12_cnt = s12_cnt
        n_prev_fetch_pc = prev_fetch_pc

        # Q1: cfg 装载 -> run 释放 -> >=2 次取指 -> trap
        if cfg_evt:
            n_s1_cfg, n_s1_run, n_s1_cnt = 1, 0, 0
        elif s1_cfg and not s1_run and run_rise:
            n_s1_run = 1
        elif s1_cfg and s1_run and fetch_done and s1_cnt < 2:
            n_s1_cnt = s1_cnt + 1
        if s1_cfg and s1_run and s1_cnt >= 2 and trap_evt:
            s["cov_seq1"] = 1
            n_s1_cfg = 0

        # Q2/Q3/Q5
        if fetch_done:
            if fetch_pc < prev_fetch_pc:
                if s2_back < 7:
                    n_s2_back = s2_back + 1
            if s3_fwd and fetch_pc < prev_fetch_pc:
                s["cov_seq3"] = 1
                n_s3_fwd = 0
            if fetch_pc > prev_fetch_pc \
                    and fetch_pc != (prev_fetch_pc + 4) & M32:
                n_s3_fwd = 1
            if fetch_pc == (prev_fetch_pc + 4) & M32:
                if s5_streak < 8:
                    n_s5_streak = s5_streak + 1
            else:
                n_s5_streak = 0
            n_prev_fetch_pc = fetch_pc
        if s2_back >= 3:
            s["cov_seq2"] = 1
        if s5_streak >= 8:
            s["cov_seq5"] = 1

        # Q4: load -> ALU -> store 同址数据流（16 位字对齐地址）
        load_done = dbus_done and not dbus_we
        stor_done = dbus_done and dbus_we
        if load_done:
            n_s4_state = 1
            n_s4_addr = dbus_addr16 & 0xFFFF
        if fetch_done and s4_state == 1 \
                and (fetch_word & 0x7F) in (0x13, 0x33):
            n_s4_state = 2
        if stor_done and s4_state == 2 \
                and s4_addr == (dbus_addr16 & 0xFFFF):
            s["cov_seq4"] = 1
            n_s4_state = 0

        # Q6: hold 连续 >=4 拍
        if hold_pre:
            if s6_cnt >= 3:
                s["cov_seq6"] = 1
            if s6_cnt < 0xFFFF:
                n_s6_cnt = s6_cnt + 1
        else:
            n_s6_cnt = 0

        # Q7: done_ok 且前一拍 hold=1
        if done_ok_pre and self.hold_d:
            s["cov_seq7"] = 1

        # Q8: busy 连续 >=8 拍
        if busy_pre:
            if s8_cnt >= 7:
                s["cov_seq8"] = 1
            if s8_cnt < 31:
                n_s8_cnt = s8_cnt + 1
        else:
            n_s8_cnt = 0

        # Q9: trap 后重启（之后取指完成 pc==0；trap_evt 拍先置位、后一拍起可命中）
        if trap_evt:
            n_s9_armed = 1
        if fetch_done and s9_armed and fetch_pc == 0:
            s["cov_seq9"] = 1
            n_s9_armed = 0

        # Q10: 全局空闲连续 >=4 拍
        idle_now = (not busy_pre) and (not hold_pre) and (not stuck_pre)
        if idle_now:
            if s10_cnt >= 3:
                s["cov_seq10"] = 1
            if s10_cnt < 15:
                n_s10_cnt = s10_cnt + 1
        else:
            n_s10_cnt = 0

        # Q11: 快速完成（run 释放后 <=64 拍内、>=1 次取指后 trap）
        if run_rise:
            n_s11_armed = 1
            n_s11_cnt = 0
            n_s11_fetch = 0
        elif s11_armed:
            if s11_cnt < 127:
                n_s11_cnt = s11_cnt + 1
            if fetch_done:
                n_s11_fetch = 1
            if s11_cnt > 64:
                n_s11_armed = 0
        if s11_armed and s11_fetch and trap_evt and s11_cnt <= 64:
            s["cov_seq11"] = 1
            n_s11_armed = 0

        # Q12: trap 驻留（stuck/hold 连续 >=2 拍）
        if stuck_pre or hold_pre:
            if s12_cnt >= 1:
                s["cov_seq12"] = 1
            if s12_cnt < 15:
                n_s12_cnt = s12_cnt + 1
        else:
            n_s12_cnt = 0

        # ---- 提交 ----
        self.s1_cfg, self.s1_run, self.s1_cnt = n_s1_cfg, n_s1_run, n_s1_cnt
        self.s2_back = n_s2_back
        self.s3_fwd = n_s3_fwd
        self.s4_state, self.s4_addr = n_s4_state, n_s4_addr
        self.s5_streak = n_s5_streak
        self.s6_cnt = n_s6_cnt
        self.s8_cnt = n_s8_cnt
        self.s9_armed = n_s9_armed
        self.s10_cnt = n_s10_cnt
        self.s11_armed, self.s11_cnt, self.s11_fetch = \
            n_s11_armed, n_s11_cnt, n_s11_fetch
        self.s12_cnt = n_s12_cnt
        self.prev_fetch_pc = n_prev_fetch_pc

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
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
            "cov_busy": self._cpu_resetn(),
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
    dut = ServPublic()
    print("serv_public local_sim loaded")
