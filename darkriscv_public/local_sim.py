#!/usr/bin/env python3
"""
darkriscv_public - Black-box simulator (local_sim.py).
Python mirror of dut/darkriscv_top.v + upstream darklife/darkriscv
(BSD-3-Clause, 3-stage RV32I pipeline, default config from dut/config.vh:
__3STAGE__ + __CSR__ + __CSR_ESSENTIAL__ + __INTERRUPT__ + __EBREAK__, IRQ=0).
The mirror reproduces the RTL cycle-accurately at the cov_* observation level
(2-state semantics: Verilator evaluates uninitialized/X as 0), verified by
cross_check.py against the Verilator build.

Hidden parameters (op_ok_set, trap_hold_n) are injected externally; the public
default placeholder OP_OK_SET = [0,0,0,0] never matches (slot value 0 is
defined to never match), so done_ok/hold are inert unless secrets are injected.

Core model notes (mirrored 1:1 from darkriscv.v):
  - 3-stage pipeline (IFPC -> IDPC -> PC), FLUSH=2 fill/bubble counter,
    XRES = RES delayed 1 cycle, HLT2/IDATA2 stall-replay registers.
  - Instruction bus: IDATA registered read (1-cycle latency), IDACK
    combinational -> IPC=1 in steady state.
  - Data bus: 1 wait state (DDACK one cycle after DDREQ) -> load/store 2
    cycles; store commits at the ACK cycle.
  - Trap: program writes stvec(0x105)=0x800 via CSRRW; EBREAK / illegal
    (IERR) / misaligned ld/st (DAER) raise the upstream exception -> IFPC
    jumps to stvec; the wrapper observes the trap-vector fetch (path A) or
    the misaligned ACK (path B), backfills the end instruction from the
    fetch history, then hold/done_ok (match) or trap_stop (no match).

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : sel 0=cfg_addr[7:0] 1=cfg_addr[15:8]
                              2=memory byte write at cfg_addr (auto-increment)
                              (accepted only while not hold)
  - set_run(run)            : run level (1=release CPU, 0=hold in reset)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
  - inject_hidden_params(op_ok_set, trap_hold_n)

CoverageSimulator (VCS-equivalent) also lives here per the interface contract
(coverage_simulator.py re-exports it).
"""

import json
import os
from typing import Dict, List, Optional

import numpy as np

# public placeholder values
PLACEHOLDER_OP_OK_SET = [0, 0, 0, 0]   # slot value 0 never matches
PLACEHOLDER_TRAP_HOLD_N = 16

M32 = 0xFFFFFFFF


def _sx(v, bits):
    """sign-extend a two's complement value of `bits` width."""
    s = 1 << (bits - 1)
    m = (1 << bits) - 1
    v &= m
    return v - 2 * s if v & s else v


class _DarkriscvCore:
    """2-state mirror of upstream darkriscv (config baked in darkriscv_top.v:
    __3STAGE__, __CSR__, __CSR_ESSENTIAL__, __INTERRUPT__, __EBREAK__, no
    threads/RV32E/M-ext/coprocessor/big-endian/flexbuzz)."""

    def __init__(self):
        self.xres = 1              # XRES (RES delayed 1 cycle, init 1)
        self.hlt2 = 0
        self.idata2 = 0
        self.iflush = 2            # FLUSH (reset value after init -1 -> 2)
        self.xidata = 0            # XIDATA (execute-stage instruction word)
        self.xlui = 0
        self.xauipc = 0
        self.xjal = 0
        self.xjalr = 0
        self.xbcc = 0
        self.xlcc = 0
        self.xscc = 0
        self.xmcc = 0
        self.xrcc = 0
        self.xcus = 0
        self.xsys = 0
        self.xsimm = 0
        self.xuimm = 0
        self.ifpc = 0
        self.idpc = 0
        self.pc = 0
        self.regs = [0] * 32
        # CSRs (__INTERRUPT__ + __EBREAK__ + __CSR_ESSENTIAL__)
        self.mstatus = 0
        self.mscratch = 0
        self.mcause = 0
        self.mepc = 0
        self.mtvec = 0
        self.mie = 0
        self.mip = 0
        self.sstatus = 0
        self.sscratch = 0
        self.scause = 0
        self.sepc = 0
        self.stvec = 0
        self.sie = 0
        self.sip = 0
        self.csrclk = 0
        self.csrins = 0

    # ------------------------------------------------------------------
    # combinational decode/bus (pre-posedge)
    # ------------------------------------------------------------------
    def comb(self, idata, datai, ddack, idack):
        x = self
        idreq = 0 if x.xres else 1
        iaddr = x.ifpc & M32
        # DDREQ = SCC||LCC (FLUSH-gated decode)
        ddreq = 1 if (not x.iflush) and (x.xscc or x.xlcc) else 0
        hlt = 1 if (ddreq and not ddack) or (idreq and not idack) else 0
        idatax = 0 if x.xres else (x.idata2 if x.hlt2 else idata)
        w = x.xidata & M32
        f3 = (w >> 12) & 7
        f7 = (w >> 25) & 0x7F
        lui = 1 if (not x.iflush) and x.xlui else 0
        auipc = 1 if (not x.iflush) and x.xauipc else 0
        jal = 1 if (not x.iflush) and x.xjal else 0
        jalr = 1 if (not x.iflush) and x.xjalr else 0
        bcc = 1 if (not x.iflush) and x.xbcc else 0
        lcc = 1 if (not x.iflush) and x.xlcc else 0
        scc = 1 if (not x.iflush) and x.xscc else 0
        mcc = 1 if (not x.iflush) and x.xmcc else 0
        rcc = 1 if (not x.iflush) and x.xrcc else 0
        cus = 1 if (not x.iflush) and x.xcus else 0
        sys = 1 if (not x.iflush) and x.xsys else 0
        dptr = (w >> 7) & 0x1F
        s1ptr = (w >> 15) & 0x1F
        s2ptr = (w >> 20) & 0x1F
        u1reg = x.regs[s1ptr] & M32
        u2reg = x.regs[s2ptr] & M32
        dreg = x.regs[dptr] & M32
        s1reg = _sx(u1reg, 32)
        s2reg = _sx(u2reg, 32)
        simm = x.xsimm & M32
        uimm = x.xuimm & M32
        daddr = (u1reg + simm) & M32
        # LDATA (little-endian, from DATAI)
        if f3 == 0 or f3 == 4:
            lane = daddr & 3
            b = (datai >> (8 * lane)) & 0xFF
            ldata = _sx(b, 8) & M32 if f3 == 0 else b
        elif f3 == 1 or f3 == 5:
            h = (datai >> 16) & 0xFFFF if (daddr & 2) else datai & 0xFFFF
            ldata = _sx(h, 16) & M32 if f3 == 1 else h
        else:
            ldata = datai & M32
        # SDATA (little-endian)
        if f3 == 0:
            lane = daddr & 3
            sdata = ((u2reg & 0xFF) << (8 * lane)) & M32
        elif f3 == 1:
            sdata = (((u2reg & 0xFFFF) << 16) & M32) if (daddr & 2) \
                else (u2reg & 0xFFFF)
        else:
            sdata = u2reg
        ebrk = 1 if (sys and f3 == 0 and (w >> 20) & 0xFFF == 1) else 0
        ierr = 0 if (x.iflush or x.xlui or x.xauipc or x.xjal or x.xjalr
                     or x.xbcc or x.xlcc or x.xscc or x.xmcc or x.xrcc
                     or x.xcus or x.xsys) else 1
        dlen = [0, 0, 0]
        if scc or lcc:
            f10 = 1 if f3 & 3 == 0 else 0
            f11 = 1 if f3 & 3 == 1 else 0
            f12 = 1 if f3 & 3 == 2 else 0
            dlen = [f10, f11, f12]
        # DBE (little-endian)
        if f3 == 0 or f3 == 4:
            lane = daddr & 3
            dbe = 8 if lane == 3 else (4 if lane == 2 else (2 if lane == 1 else 1))
        elif f3 == 1 or f3 == 5:
            dbe = 0xC if (daddr & 2) else 0x3
        else:
            dbe = 0xF
        drw = 0 if scc else 1
        drd = 1 if lcc else 0
        dwr = 1 if scc else 0
        datao = sdata
        # CSR
        csrx = 1 if (sys and (f3 & 3)) else 0
        mret = 1 if (sys and f3 == 0 and (w >> 20) & 0xFFF == 0x302) else 0
        sret = 1 if (sys and f3 == 0 and (w >> 20) & 0xFFF == 0x102) else 0
        csr = (w >> 20) & 0xFFF
        crdata = (
            0 if csr == 0xf14 else
            x.mip if csr == 0x344 else
            x.mie if csr == 0x304 else
            x.mepc if csr == 0x341 else
            x.mcause if csr == 0x342 else
            x.mtvec if csr == 0x305 else
            x.mstatus if csr == 0x300 else
            x.mscratch if csr == 0x340 else
            x.sip if csr == 0x144 else
            x.sie if csr == 0x104 else
            x.sepc if csr == 0x141 else
            x.scause if csr == 0x142 else
            x.stvec if csr == 0x105 else
            x.sstatus if csr == 0x100 else
            x.sscratch if csr == 0x140 else
            (x.csrclk & M32) if csr == 0xC00 else
            (x.csrins & M32) if csr == 0xC02 else
            ((x.csrclk >> 32) & M32) if csr == 0xC80 else
            ((x.csrins >> 32) & M32) if csr == 0xC82 else
            0) & M32
        crmask = ((w >> 15) & 0x1F) if (f3 & 4) else u1reg
        wrdata = ((crdata & (~crmask & M32)) & M32) if (f3 & 3) == 3 else \
            ((crdata | crmask) & M32) if (f3 & 3) == 2 else crmask & M32
        # RM group
        s2regx = simm if mcc else s2reg
        u2regx = simm if mcc else u2reg
        if f3 == 7:
            rmdata = (u1reg & s2regx) & M32
        elif f3 == 6:
            rmdata = (u1reg | s2regx) & M32
        elif f3 == 4:
            rmdata = (u1reg ^ s2regx) & M32
        elif f3 == 3:
            rmdata = 1 if u1reg < u2regx else 0
        elif f3 == 2:
            rmdata = 1 if s1reg < _sx(s2regx, 32) else 0
        elif f3 == 0:
            rmdata = ((u1reg - s2regx) & M32) if (rcc and (f7 & 0x20)) \
                else ((u1reg + s2regx) & M32)
        elif f3 == 1:
            rmdata = (s1reg << (u2regx & 0x1F)) & M32
        else:
            if not (f7 & 0x20):
                rmdata = (u1reg >> (u2regx & 0x1F)) & M32   # logical (>>)
            else:
                rmdata = (s1reg >> (u2regx & 0x1F)) & M32   # arithmetic (>>>)
        # J/B group
        bmux = 1 if ((f3 == 7 and u1reg >= u2reg)
                     or (f3 == 6 and u1reg < u2regx)
                     or (f3 == 5 and s1reg >= _sx(s2regx, 32))
                     or (f3 == 4 and s1reg < _sx(s2regx, 32))
                     or (f3 == 1 and u1reg != u2regx)
                     or (f3 == 0 and u1reg == u2regx)) else 0
        pcsimm = (x.pc + simm) & M32
        jreq = 1 if (jal or jalr or (bcc and bmux)) else 0
        jval = ((daddr >> 2) << 2) & M32 if jalr else ((pcsimm >> 2) << 2) & M32
        daer = 1 if (dlen[1] and (daddr & 1)) or (dlen[2] and (daddr & 3)) else 0
        iaer = 1 if (iaddr & 3) else 0
        return {
            "idreq": idreq, "iaddr": iaddr, "ddreq": ddreq, "hlt": hlt,
            "idatax": idatax, "w": w, "f3": f3, "f7": f7,
            "lui": lui, "auipc": auipc, "jal": jal, "jalr": jalr,
            "bcc": bcc, "lcc": lcc, "scc": scc, "mcc": mcc, "rcc": rcc,
            "cus": cus, "sys": sys, "dptr": dptr, "u1reg": u1reg,
            "u2reg": u2reg, "dreg": dreg, "simm": simm,
            "daddr": daddr, "ldata": ldata, "sdata": sdata,
            "ebrk": ebrk, "ierr": ierr, "dlen": dlen, "dbe": dbe,
            "drw": drw, "drd": drd, "dwr": dwr, "datao": datao,
            "csrx": csrx, "mret": mret, "sret": sret, "csr": csr,
            "crdata": crdata, "wrdata": wrdata, "rmdata": rmdata,
            "bmux": bmux, "pcsimm": pcsimm, "jreq": jreq, "jval": jval,
            "daer": daer, "iaer": iaer,
        }

    # ------------------------------------------------------------------
    def posedge(self, res, idata, datai, ddack, idack):
        """One posedge. All inputs are pre-posedge values."""
        x = self
        c = x.comb(idata, datai, ddack, idack)
        hlt = c["hlt"]
        xres = x.xres
        idatax = c["idatax"]
        w = c["w"]
        exc = 1 if (c["ierr"] or c["ebrk"] or c["daer"] or c["iaer"]) else 0

        # ---- FLUSH ----
        if xres:
            new_flush = 2
        elif hlt:
            new_flush = x.iflush
        elif x.iflush:
            new_flush = (x.iflush - 1) & 3
        elif exc or c["sret"] or c["mret"] or c["jreq"]:
            new_flush = 2
        else:
            new_flush = 0

        # ---- CSR_ESSENTIAL counters ----
        if not xres:
            x.csrclk = (x.csrclk + 1) & ((1 << 64) - 1)
            if not hlt and x.iflush == 0:
                x.csrins = (x.csrins + 1) & ((1 << 64) - 1)

        # ---- INTERRUPT block (IRQ=0) ----
        new_mip = 0 if xres else x.mip
        new_mstatus = x.mstatus
        new_mscratch = x.mscratch
        new_mcause = x.mcause
        new_mepc = x.mepc
        new_mtvec = x.mtvec
        new_mie = x.mie
        if xres:
            new_mtvec = 0
            new_mepc = 0
            new_mie = 0
            new_mcause = 0
            new_mstatus = 0
            new_mscratch = 0
        elif (not hlt) and x.iflush == 0:
            if c["csrx"]:
                csr = c["csr"]
                if csr == 0x300:
                    new_mstatus = c["wrdata"]
                elif csr == 0x340:
                    new_mscratch = c["wrdata"]
                elif csr == 0x305:
                    new_mtvec = c["wrdata"]
                elif csr == 0x341:
                    new_mepc = c["wrdata"]
                elif csr == 0x304:
                    new_mie = c["wrdata"]
            elif x.mip & 0x800 and c["jreq"]:
                new_mepc = c["jval"]
                new_mstatus = (x.mstatus & ~0x8) & M32
                new_mstatus = (new_mstatus & ~0x80) | ((x.mstatus & 0x8) << 4)
                new_mcause = 0x8000000B
            elif c["mret"]:
                new_mstatus = (x.mstatus & ~0x8) | ((x.mstatus & 0x80) >> 4)

        # ---- EBREAK block ----
        new_sstatus = x.sstatus
        new_sscratch = x.sscratch
        new_scause = x.scause
        new_sepc = x.sepc
        new_stvec = x.stvec
        new_sie = x.sie
        new_sip = x.sip
        if xres:
            new_stvec = 0
            new_sepc = 0
            new_sie = 0
            new_sip = 0
            new_scause = 0
            new_sstatus = 0
            new_sscratch = 0
        elif (not hlt) or x.iflush == 0:
            if x.stvec and exc:
                new_sepc = x.pc & M32
                new_sstatus = (x.sstatus & ~0x2) & M32
                new_sstatus = (new_sstatus & ~0x20) \
                    | ((x.sstatus & 0x2) << 4)
                new_scause = (0 if c["iaer"] else
                              2 if c["ierr"] else
                              3 if c["ebrk"] else
                              4 if (c["daer"] and c["drd"]) else
                              6 if (c["daer"] and c["dwr"]) else -1) & M32
                new_sip = x.sip | 0x2
            elif c["csrx"]:
                csr = c["csr"]
                if csr == 0x100:
                    new_sstatus = c["wrdata"]
                elif csr == 0x140:
                    new_sscratch = c["wrdata"]
                elif csr == 0x105:
                    new_stvec = c["wrdata"]
                elif csr == 0x141:
                    new_sepc = c["wrdata"]
                elif csr == 0x104:
                    new_sie = c["wrdata"]
            elif c["sret"]:
                new_sstatus = (x.sstatus & ~0x8) | ((x.sstatus & 0x80) >> 4)
                new_sip = x.sip & ~0x2

        # ---- REGS writeback (runs EVERY posedge: during reset the stale
        #      XIDATA's rd field is zeroed, mirroring upstream `REGS[DPTR] <=
        #      XRES||DPTR==0 ? 0 : ...` with DPTR = XIDATA[11:7]) ----
        dptr = c["dptr"]
        if xres or dptr == 0:
            wrdata = 0
        elif hlt:
            wrdata = c["dreg"]
        elif c["lcc"]:
            wrdata = c["ldata"]
        elif c["auipc"]:
            wrdata = c["pcsimm"]
        elif c["jal"] or c["jalr"]:
            wrdata = x.idpc & M32
        elif c["lui"]:
            wrdata = c["simm"]
        elif c["mcc"] or c["rcc"]:
            wrdata = c["rmdata"]
        elif c["csrx"]:
            wrdata = c["crdata"]
        else:
            wrdata = c["dreg"]
        x.regs[dptr] = wrdata & M32

        # ---- IFPC / IDPC / PC ----
        if xres:
            new_ifpc = 0
        elif hlt:
            new_ifpc = x.ifpc
        elif c["sret"]:
            new_ifpc = x.sepc & M32
        elif x.stvec and exc:
            new_ifpc = x.stvec & M32
        elif c["mret"]:
            new_ifpc = x.mepc & M32
        elif (x.mip & 0x800) and c["jreq"]:
            new_ifpc = x.mtvec & M32
        elif c["jreq"]:
            new_ifpc = c["jval"]
        else:
            new_ifpc = (x.ifpc + 4) & M32

        new_idpc = x.idpc if hlt else x.ifpc
        new_pc = x.pc if hlt else x.idpc

        # ---- XIDATA / decode regs ----
        def dec_bits(dw):
            return (
                1 if dw & 0x7F == 0x37 else 0,
                1 if dw & 0x7F == 0x17 else 0,
                1 if dw & 0x7F == 0x6F else 0,
                1 if dw & 0x7F == 0x67 else 0,
                1 if dw & 0x7F == 0x63 else 0,
                1 if dw & 0x7F == 0x03 else 0,
                1 if dw & 0x7F == 0x23 else 0,
                1 if dw & 0x7F == 0x13 else 0,
                1 if dw & 0x7F == 0x33 else 0,
                1 if dw & 0x7F == 0x0B else 0,
                1 if dw & 0x7F == 0x73 else 0,
            )
        if hlt:
            new_xidata = x.xidata
            nx = (x.xlui, x.xauipc, x.xjal, x.xjalr, x.xbcc, x.xlcc, x.xscc,
                  x.xmcc, x.xrcc, x.xcus, x.xsys)
            new_xsimm = x.xsimm
            new_xuimm = x.xuimm
        else:
            dw = idatax & M32
            new_xidata = dw
            nx = dec_bits(dw)
            op = dw & 0x7F
            if op == 0x23:
                new_xsimm = _sx(((dw >> 25) & 0x7F) << 5 | (dw >> 7) & 0x1F, 12) & M32
                new_xuimm = (((dw >> 25) & 0x7F) << 5 | (dw >> 7) & 0x1F) & M32
            elif op == 0x63:
                b = (((dw >> 31) & 1) << 12) | (((dw >> 7) & 1) << 11) \
                    | (((dw >> 25) & 0x3F) << 5) | (((dw >> 8) & 0xF) << 1)
                new_xsimm = _sx(b, 13) & M32
                new_xuimm = b & M32
            elif op == 0x6F:
                j = (((dw >> 31) & 1) << 20) | (((dw >> 12) & 0xFF) << 12) \
                    | (((dw >> 20) & 1) << 11) | (((dw >> 21) & 0x3FF) << 1)
                new_xsimm = _sx(j, 21) & M32
                new_xuimm = j & M32
            elif op == 0x37 or op == 0x17:
                new_xsimm = (dw & 0xFFFFF000) & M32
                new_xuimm = (dw & 0xFFFFF000) & M32
            else:
                new_xsimm = _sx((dw >> 20) & 0xFFF, 12) & M32
                new_xuimm = (dw >> 20) & 0xFFF

        # ---- XRES / HLT2 / IDATA2 ----
        new_xres = 1 if res else 0
        new_hlt2 = 1 if hlt else 0
        new_idata2 = idata & M32 if (x.hlt2 ^ hlt) else x.idata2

        # ---- commit ----
        x.xres = new_xres
        x.hlt2 = new_hlt2
        x.idata2 = new_idata2
        x.iflush = new_flush
        x.xidata = new_xidata
        (x.xlui, x.xauipc, x.xjal, x.xjalr, x.xbcc, x.xlcc, x.xscc,
         x.xmcc, x.xrcc, x.xcus, x.xsys) = nx
        x.xsimm = new_xsimm
        x.xuimm = new_xuimm
        x.ifpc = new_ifpc
        x.idpc = new_idpc
        x.pc = new_pc
        x.mip = new_mip
        x.mstatus = new_mstatus
        x.mscratch = new_mscratch
        x.mcause = new_mcause
        x.mepc = new_mepc
        x.mtvec = new_mtvec
        x.mie = new_mie
        x.sstatus = new_sstatus
        x.sscratch = new_sscratch
        x.scause = new_scause
        x.sepc = new_sepc
        x.stvec = new_stvec
        x.sie = new_sie
        x.sip = new_sip
        return c


class DarkriscvPublic:
    """Black-box simulator for darkriscv_public (mirrors dut/darkriscv_top.v)."""

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
        self.cpu = _DarkriscvCore()
        self.imem = [0] * 1024
        self.dmem = [0] * 1024
        self.cfg_addr = 0
        # action inputs (per-cycle)
        self._cfg_wr = 0
        self._cfg_sel = 0
        self._cfg_data = 0
        self.run = 0
        # wrapper regs
        self.idata_r = 0
        self.dd_state = 0
        self.datai_q = 0
        self.xres_q = 1
        self.hlt2_q = 0
        self.idata2_q = 0
        self.idata2_addr_q = 0
        self.iaddr_q = 0
        self.hist0_pc = 0
        self.hist0_insn = 0
        self.hist1_pc = 0
        self.hist1_insn = 0
        self.hist2_pc = 0
        self.hist2_insn = 0
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
        self.trap_stop = 0
        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0
        self.seq = {k: 0 for k in
                    ("cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4",
                     "cov_seq5", "cov_seq6", "cov_seq7", "cov_seq8",
                     "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12")}
        # monitors
        self.prev_fetch_pc = 0
        self.run_d = 0
        self.hold_d = 0
        self.tstop_d = 0
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
    def step(self):
        """Advance one clock cycle (mirrors darkriscv_top always blocks)."""
        cpu = self.cpu

        # ---- pre-posedge wrapper combinational ----
        core_res = 0 if (self.run and not self.cov_hold) else 1
        # core combinational (needs acks)
        idreq = 0 if cpu.xres else 1
        ddreq_pre = 1 if (not cpu.iflush) and (cpu.xscc or cpu.xlcc) else 0
        idack = 1 if (idreq and not self.cov_hold and not self.trap_stop) else 0
        ddack = 1 if (ddreq_pre and self.dd_state
                      and not self.cov_hold and not self.trap_stop) else 0
        hlt = 1 if (ddreq_pre and not ddack) or (idreq and not idack) else 0
        iaddr_pre = cpu.ifpc & M32
        cfg_ok = 1 if (self._cfg_wr and not self.cov_hold) else 0

        # HLT2/IDATA2 replay mirror + IDATAX
        if cpu.xres:
            idatax = 0
            idatax_addr = 0
        elif self.hlt2_q:
            idatax = self.idata2_q
            idatax_addr = self.idata2_addr_q
        else:
            idatax = self.idata_r
            idatax_addr = self.iaddr_q

        # trap detection (pre-posedge)
        # path A: non-sequential trap-vector fetch (fetch-ahead = PC+8 can
        # sequentially sweep over 0x800 when PC >= 0x7F8; filtered)
        tvec_req = 1 if (idreq and not cpu.xres and iaddr_pre == 0x800
                         and iaddr_pre != ((self.iaddr_q + 4) & M32)
                         and not self.cov_hold and not self.trap_stop) else 0
        daddr_pre = 0
        daer = 0
        if ddreq_pre:
            c2 = cpu.comb(self.idata_r, self.datai_q, ddack, idack)
            daddr_pre = c2["daddr"]
            daer = 1 if (c2["dlen"][1] and (daddr_pre & 1)) \
                or (c2["dlen"][2] and (daddr_pre & 3)) else 0
        ldst_trap = 1 if (ddack and daer and not self.cov_hold
                          and not self.trap_stop) else 0
        trap_rise = 1 if (tvec_req or ldst_trap) else 0
        end_pc = (self.hist0_pc if ldst_trap else self.hist1_pc) & M32
        end_insn = (self.hist0_insn if ldst_trap else self.hist1_insn) & M32
        end_opcode = end_insn & 0x7F
        m0 = 1 if end_opcode and end_opcode == self.op_ok_set[0] else 0
        m1 = 1 if end_opcode and end_opcode == self.op_ok_set[1] else 0
        m2 = 1 if end_opcode and end_opcode == self.op_ok_set[2] else 0
        m3 = 1 if end_opcode and end_opcode == self.op_ok_set[3] else 0
        trap_match = 1 if (m0 or m1 or m2 or m3) else 0
        trap_class = 0 if m0 else (1 if m1 else (2 if m2 else 3))

        # ---- pre-posedge snapshots used by post-posedge updates ----
        xres_pre = cpu.xres
        hist1_insn_pre = self.hist1_insn
        iaddr_q_pre = self.iaddr_q
        dd_state_pre = self.dd_state
        hold_pre = self.cov_hold
        tstop_pre = self.trap_stop
        done_ok_pre = self.cov_done_ok_valid
        run_d_pre = self.run_d

        # ---- memory read for this cycle (idata_r holds pre-posedge value) ----
        idata_pre = self.idata_r
        datai_pre = self.datai_q

        # ---- core posedge ----
        c = cpu.posedge(core_res, idata_pre, datai_pre, ddack, idack)

        # ---- wrapper posedge updates (pre-posedge snapshots) ----
        # cfg write first, then CPU store commit (store wins on conflict)
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
                    self.dmem[w] = ((self.dmem[w]
                                     & ~(0xFF << (8 * lane)))
                                    | (self._cfg_data << (8 * lane))) & M32
                else:
                    self.imem[w] = ((self.imem[w]
                                     & ~(0xFF << (8 * lane)))
                                    | (self._cfg_data << (8 * lane))) & M32
                self.cfg_addr = (self.cfg_addr + 1) & 0xFFFF
        # CPU store commit (ACK cycle)
        if ddack and c["dwr"]:
            w = (daddr_pre >> 2) & 0x3FF
            d = self.dmem[w]
            if c["dbe"] & 1:
                d = (d & ~0xFF) | (c["datao"] & 0xFF)
            if c["dbe"] & 2:
                d = (d & ~0xFF00) | (c["datao"] & 0xFF00)
            if c["dbe"] & 4:
                d = (d & ~0xFF0000) | (c["datao"] & 0xFF0000)
            if c["dbe"] & 8:
                d = (d & ~0xFF000000) | (c["datao"] & 0xFF000000)
            self.dmem[w] = d & M32
        # idata_r (registered instruction read; pre-posedge iaddr)
        self.idata_r = self.imem[(iaddr_pre >> 2) & 0x3FF]
        # dd_state / datai_q
        if self.cov_hold or not self.run:
            new_dd_state = 0
        elif ddreq_pre and not dd_state_pre:
            new_dd_state = 1
        elif dd_state_pre:
            new_dd_state = 0
        else:
            new_dd_state = 0
        self.dd_state = new_dd_state
        if ddreq_pre and not dd_state_pre and not self.cov_hold \
                and not self.trap_stop:
            self.datai_q = self.dmem[(daddr_pre >> 2) & 0x3FF]
        # xres_q / hlt2 / idata2 mirror
        self.xres_q = 1 if core_res else 0
        hlt2_pre = self.hlt2_q
        self.hlt2_q = 1 if hlt else 0
        if hlt2_pre ^ hlt:
            self.idata2_q = idata_pre
            self.idata2_addr_q = self.iaddr_q
        # iaddr_q / fetch history
        self.iaddr_q = iaddr_pre
        lat_evt = 1 if (not hlt and not xres_pre) else 0
        if lat_evt:
            self.hist2_pc = self.hist1_pc
            self.hist2_insn = self.hist1_insn
            self.hist1_pc = self.hist0_pc
            self.hist1_insn = self.hist0_insn
            self.hist0_pc = idatax_addr
            self.hist0_insn = idatax

        # ---- cov registers ----
        self.cov_cfg_ok = cfg_ok
        if lat_evt:
            self.cov_pc = idatax_addr & M32
            self.cov_instr = idatax & M32
            self.cov_mem_addr = idatax_addr & 0xFFFF
            self.cov_mem_rdata = idatax & 0xFFFF
            self.cov_mem_wstrb = 0
            self.cov_mem_rd = 1
            self.cov_mem_instr = 1
            if self.cov_instr_cnt != 0xFF:
                self.cov_instr_cnt = (self.cov_instr_cnt + 1) & 0xFF
        if ddack:
            self.cov_mem_addr = daddr_pre & 0xFFFF
            self.cov_mem_wdata = c["datao"] & 0xFFFF
            self.cov_mem_rdata = datai_pre & 0xFFFF
            self.cov_mem_wstrb = 0 if c["drd"] else c["dbe"]
            self.cov_mem_rd = c["drd"]
            self.cov_mem_instr = 0
        self.cov_branch_taken = 1 if (
            (hist1_insn_pre & 0x7F) == 0x63
            and iaddr_pre != ((iaddr_q_pre + 4) & M32)) else 0
        if trap_rise:
            self.cov_instr = end_insn
            self.cov_pc = end_pc

        # ---- trap / hold FSM ----
        self.cov_trap = trap_rise
        self.cov_done_ok_valid = 0
        if trap_rise and not trap_match:
            self.trap_stop = 1
        elif not self.run:
            self.trap_stop = 0
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
        busy_pre = 1 if (not xres_pre and not hold_pre and not tstop_pre) else 0
        run_rise = 1 if (self.run and not run_d_pre) else 0
        load_done = 1 if (ddack and c["drd"]) else 0
        stor_done = 1 if (ddack and c["dwr"]) else 0
        self._monitor_step(
            cfg_evt=cfg_ok, run_rise=run_rise, lat_evt=lat_evt,
            load_done=load_done, stor_done=stor_done, trap_rise=trap_rise,
            busy_pre=busy_pre, hold_pre=hold_pre, done_ok_pre=done_ok_pre,
            tstop_pre=tstop_pre,
            fetch_pc=idatax_addr, fetch_word=idatax,
            mem_addr=daddr_pre)

        # ---- trailing registers ----
        self.run_d = 1 if self.run else 0
        self.hold_d = hold_pre
        self.tstop_d = tstop_pre
        self._cfg_wr = 0

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_evt, run_rise, lat_evt, load_done, stor_done,
                      trap_rise, busy_pre, hold_pre, done_ok_pre, tstop_pre,
                      fetch_pc, fetch_word, mem_addr):
        """Mirror of the darkriscv_top temporal-sequence monitor (1:1).
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
        elif self.s1_cfg and self.s1_run and lat_evt and self.s1_cnt < 2:
            self.s1_cnt += 1
        if self.s1_cfg and self.s1_run and self.s1_cnt >= 2 and trap_rise:
            s["cov_seq1"] = 1
            self.s1_cfg = 0

        # Q2/Q3/Q5: 取指流（比较一律用更新前的计数值，与 RTL 一致）
        s2_old = self.s2_back
        s5_old = self.s5_streak
        if lat_evt:
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

        # Q4: load -> ALU -> store 同址数据流（trap 重启清状态；load 的 ACK
        # 拍恰是下一条指令进入流水线的锁存拍，若该字即 ALU 直接进入 state2）
        if trap_rise:
            self.s4_state = 0
        if load_done:
            self.s4_state = 1
            self.s4_addr = mem_addr & 0xFFFF
            if (fetch_word & 0x7F) in (0x13, 0x33):
                self.s4_state = 2
        if lat_evt and self.s4_state == 1 \
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
        if lat_evt and self.s9_armed and fetch_pc == 0:
            s["cov_seq9"] = 1
            self.s9_armed = 0

        # Q10: 全局空闲连续 >=4 拍
        idle_now = (not busy_pre) and (not hold_pre) and (not tstop_pre)
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
            if lat_evt:
                self.s11_fetch = 1
            if self.s11_cnt > 64:
                self.s11_armed = 0
        if self.s11_armed and self.s11_fetch and trap_rise \
                and self.s11_cnt <= 64:
            s["cov_seq11"] = 1
            self.s11_armed = 0

        # Q12: trap 一致性（非匹配陷阱后冻结保持）
        if tstop_pre and self.tstop_d:
            s["cov_seq12"] = 1

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        cpu = self.cpu
        busy = 1 if (not cpu.xres and not self.cov_hold
                     and not self.trap_stop) else 0
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


# ===========================================================================
# CoverageSimulator (VCS-equivalent; re-exported by coverage_simulator.py)
# ===========================================================================
class CoverageSimulator:
    def __init__(self, meta_path: str, trap_hold_n: int = 16):
        with open(meta_path, "r", encoding="utf-8") as f:
            self.meta = json.load(f)
        self.coverpoints = self.meta["coverpoints"]
        self.trap_hold_n = trap_hold_n
        self.total_bins = 0
        self.reset()

    def reset(self) -> np.ndarray:
        self.hit_bins = 0
        self.bin_counts = {}
        self.total_bins = 0
        for cp in self.coverpoints:
            self.bin_counts[cp["name"]] = {}
            for b in cp.get("bins", []):
                self.bin_counts[cp["name"]][b["name"]] = 0
                self.total_bins += 1
        self._reset_trackers()
        return self._vector()

    # -- cross-cycle trackers (deep + sva) ----------------------------------
    def _reset_trackers(self):
        self._ds_hold_run = 0
        self._ds_hold_max = 0
        self._ds_hold_hit = False
        self._ds_class_first = None
        self._ds_class_switch = False
        self._ds_prev_cnt = None
        self._ds_opcode_set = set()
        self._ds_opcode_hit = False
        self._df_busy_run = 0
        self._df_busy_max = 0
        self._tp_hold_run = 0
        self._tp_hold_max = 0
        self._tp_idle_run = 0
        self._tp_idle_max = 0

    def _update_trackers(self, signals: Dict):
        hold = int(signals.get("cov_hold", 0) or 0)
        busy = int(signals.get("cov_busy", 0) or 0)
        trap = int(signals.get("cov_trap", 0) or 0)
        done_ok = int(signals.get("cov_done_ok_valid", 0) or 0)
        opcode = int(signals.get("cov_opcode", 0) or 0)
        cnt = int(signals.get("cov_instr_cnt", 0) or 0)

        if hold == 1:
            self._ds_hold_run += 1
        else:
            self._ds_hold_run = 0
        if self._ds_hold_run > self._ds_hold_max:
            self._ds_hold_max = self._ds_hold_run
        if self._ds_hold_max >= self.trap_hold_n - 1:
            self._ds_hold_hit = True

        if done_ok:
            cls = int(signals.get("cov_done_ok_class", 0) or 0)
            if self._ds_class_first is None:
                self._ds_class_first = cls
            elif cls != self._ds_class_first:
                self._ds_class_switch = True

        if self._ds_prev_cnt is not None and cnt != self._ds_prev_cnt:
            self._ds_opcode_set.add(opcode & 0x7F)
        self._ds_prev_cnt = cnt
        if len(self._ds_opcode_set) >= 4:
            self._ds_opcode_hit = True

        if self._ds_hold_hit:
            self._hit("ds_hold_window_max", "hold_window_hit")
        if self._ds_class_switch:
            self._hit("ds_done_ok_class_switch", "class_switch_hit")
        if self._ds_opcode_hit:
            self._hit("ds_opcode_diversity", "opcode_div_hit")

        if busy == 1:
            self._df_busy_run += 1
            if self._df_busy_run > self._df_busy_max:
                self._df_busy_max = self._df_busy_run
        else:
            self._df_busy_run = 0
        for b in (2, 4, 8):
            if self._df_busy_max >= b:
                self._hit("dataflow_busy_streak", "busy%d" % b)

        for b, name in ((1, "act1"), (8, "act8"), (16, "act16")):
            if self._df_busy_max >= b:
                self._hit("timing_active_dwell", name)

        if hold == 1:
            self._tp_hold_run += 1
            if self._tp_hold_run > self._tp_hold_max:
                self._tp_hold_max = self._tp_hold_run
        else:
            self._tp_hold_run = 0
        if self._tp_hold_max >= 4:
            self._hit("timing_hold_dwell", "hold4")
        if self._tp_hold_max >= self.trap_hold_n - 1:
            self._hit("timing_hold_dwell", "holdfull")

        idle = (busy == 0 and hold == 0 and trap == 0)
        if idle:
            self._tp_idle_run += 1
            if self._tp_idle_run > self._tp_idle_max:
                self._tp_idle_max = self._tp_idle_run
        else:
            self._tp_idle_run = 0
        if self._tp_idle_max >= 4:
            self._hit("timing_idle_dwell", "idle4")
        if self._tp_idle_max >= 16:
            self._hit("timing_idle_dwell", "idle16")

    def _target_signal(self, cp) -> str:
        sig = cp.get("signal", "")
        return sig.split(",")[0].strip()

    def step(self, signals: Dict) -> np.ndarray:
        for cp in self.coverpoints:
            t = cp["type"]
            if t == "cross":
                self._process_cross(cp, signals)
            elif t == "seq_hit":
                self._process_seq(cp, signals)
            elif t in ("deep", "sva"):
                pass
            else:
                self._process_leaf(cp, signals)
        self._update_trackers(signals)
        return self._vector()

    def _process_seq(self, cp, signals):
        name = cp["name"]
        flag = cp.get("seq", "")
        if not flag:
            return
        if signals.get(flag):
            for b in cp.get("bins", []):
                self._hit(name, b["name"])

    def _process_leaf(self, cp, signals):
        name = cp["name"]
        sig = self._target_signal(cp)
        val = signals.get(sig)
        if val is None:
            return
        if isinstance(val, bool):
            val = 1 if val else 0
        val = int(val)
        if cp["type"] == "temporal":
            vflag = cp.get("valid_signal", "cov_done_ok_valid")
            if not signals.get(vflag, False):
                return
            want = val
        else:
            want = val
        for b in cp.get("bins", []):
            if int(b["value"]) == want:
                self._hit(name, b["name"])

    def _process_cross(self, cp, signals):
        name = cp["name"]
        parents = [s.strip() for s in cp.get("signal", "").split(",")]
        raw = [signals.get(p) for p in parents]
        if any(v is None for v in raw):
            return
        if "cov_done_ok_class" in parents:
            if not signals.get("cov_done_ok_valid", False):
                return
        raw = [1 if isinstance(v, bool) and v else int(v) for v in raw]
        for b in cp.get("bins", []):
            combo = b["cross"]
            if len(combo) != len(raw):
                continue
            if all(int(raw[k]) == int(combo[k]) for k in range(len(combo))):
                self._hit(name, b["name"])

    def _hit(self, cp_name, bin_name):
        if self.bin_counts[cp_name][bin_name] == 0:
            self.hit_bins += 1
        self.bin_counts[cp_name][bin_name] += 1

    @property
    def covered_bins(self):
        return self.hit_bins

    @property
    def coverage(self):
        return self.hit_bins / self.total_bins if self.total_bins else 0.0

    def get_coverage(self) -> dict:
        return {
            "total_bins": self.total_bins,
            "hit_bins": self.hit_bins,
            "coverage_pct": (self.hit_bins / self.total_bins * 100) if self.total_bins else 0,
            "bin_counts": self.bin_counts,
        }

    def get_bin_vector(self) -> List[int]:
        return list(self._vector())

    def get_state(self) -> np.ndarray:
        return self._vector()

    def _vector(self) -> np.ndarray:
        vec = np.zeros(self.total_bins, dtype=np.float32)
        i = 0
        for cp in self.coverpoints:
            for b in cp.get("bins", []):
                if self.bin_counts[cp["name"]][b["name"]] > 0:
                    vec[i] = 1.0
                i += 1
        return vec


if __name__ == "__main__":
    here = os.path.dirname(os.path.abspath(__file__))
    dut = DarkriscvPublic()
    sim = CoverageSimulator(os.path.join(here, "dut", "coverage_meta.json"))
    print("darkriscv_public local_sim loaded, total bins:", sim.total_bins)
