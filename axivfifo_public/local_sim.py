#!/usr/bin/env python3
"""
axivfifo_public - Black-box simulator (local_sim.py).
Cycle-accurate Python mirror of dut/axivfifo_top.v (+ the upstream
alexforencich/verilog-axi axi_vfifo internals) for local development and
evaluation. Verified against the Verilator-built RTL by cross_check.py
(30000-cycle directed-random stimulus, 0 mismatches on the full cov_* bus).

Configuration (matches dut/axivfifo_top.v):
  AXI_CH=2, AXI_DATA_WIDTH=32, AXI_ADDR_WIDTH=16, AXIS_DATA_WIDTH=32,
  AXIS_KEEP_WIDTH=4, SEG_WIDTH=32, SEG_CNT=2 (encoder) / CH_SEG_CNT=1
  (per-channel raw modules), AXI_ID_WIDTH=8, AXI_MAX_BURST_LEN=16,
  WRITE_FIFO_DEPTH=64, READ_FIFO_DEPTH=128, WRITE/READ_MAX_BURST_LEN=16,
  LEN_WIDTH=16, MAX_SEG_WIDTH=256.
The 1-channel configurations are structurally broken upstream (the encoder's
SEG_CNT=1 output mux cannot emit the byte-aligned block stream - the upstream
testbench comments out all single-channel parameter sets).

Hidden parameters (len_ok_set, done_hold_n) are injected externally; the
public default placeholder LEN_OK_SET = [0,0,0,0] has no matching value
(value 0 never matches by convention), so done_ok is inert unless secrets
are injected. The trigger observes channel 0's write bursts:
fully-enqueued burst (AW handshake done + W last beat accepted) whose AWLEN
matches a non-zero slot -> hold window -> done_ok (class = slot).
"""

from typing import Dict, List, Optional

# ---------------------------------------------------------------------------
# fixed configuration (mirrors dut/axivfifo_top.v)
# ---------------------------------------------------------------------------
AXI_CH = 2
AXI_DATA_WIDTH = 32
AXI_ADDR_WIDTH = 16
AXI_ID_WIDTH = 8
AXI_MAX_BURST_LEN = 16
WRITE_FIFO_DEPTH = 64
READ_FIFO_DEPTH = 128
LEN_WIDTH = 16
SEG_WIDTH = 32

# encoder/decoder derived params (SEG_CNT=2 at the stream side)
SEG_CNT = 2
SEG_CNT_INT = 2
SEG_IDX_WIDTH = 1
SEG_IDX_MASK = (1 << SEG_IDX_WIDTH) - 1
AXIS_BYTE_LANES = 4
BYTE_SIZE = 8
SEG_BYTE_LANES = SEG_WIDTH // BYTE_SIZE          # 4
SEG_BYTE_IDX_WIDTH = 2
AXIS_SEG_CNT = 1
AXIS_SEG_IDX_WIDTH = 1
META_WIDTH = 1
HDR_SIZE = (16 + META_WIDTH + BYTE_SIZE - 1) // BYTE_SIZE   # 3
HDR_WIDTH = HDR_SIZE * BYTE_SIZE                           # 24
HDR_LEN_WIDTH = 12
INPUT_FIFO_ADDR_WIDTH = 5
HDR_FIFO_ADDR_WIDTH = INPUT_FIFO_ADDR_WIDTH + SEG_IDX_WIDTH  # 6
INPUT_FIFO_SIZE = SEG_BYTE_LANES * SEG_CNT_INT * 2 ** INPUT_FIFO_ADDR_WIDTH
MAX_BLOCK_LEN = min(INPUT_FIFO_SIZE // 2, 4096)               # 128

# raw wr/rd derived params (per channel: CH_SEG_CNT=1, SEG_WIDTH=32)
AXI_BYTE_LANES_RAW = AXI_DATA_WIDTH // 8   # 4
AXI_BURST_SIZE = 2
WRITE_FIFO_ADDR_WIDTH = 6
READ_FIFO_ADDR_WIDTH = 7
WRITE_MAX_BURST_LEN_INT = 16
WRITE_BURST_LEN_WIDTH = 4
WRITE_BURST_ADDR_WIDTH = 6
WRITE_BURST_ADDR_MASK = 0x3F
READ_MAX_BURST_LEN_INT = 16
READ_BURST_LEN_WIDTH = 4
READ_BURST_ADDR_WIDTH = 6
READ_BURST_ADDR_MASK = 0x3F
WATERMARK_LEVEL = WRITE_FIFO_DEPTH - 4    # 60
ADDR_MASK = 0xFFFF << AXI_BURST_SIZE      # 0xFFFC

# dec derived params
CTRL_FIFO_ADDR_WIDTH = 5
OUTPUT_FIFO_ADDR_WIDTH = 5
CTRL_FIFO_PTR_WIDTH = CTRL_FIFO_ADDR_WIDTH + SEG_IDX_WIDTH   # 6

# public placeholder values
PLACEHOLDER_LEN_OK_SET = [0, 0, 0, 0]   # 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16


def _xor_reduce_shift(gray, k):
    """RTL: sync[k] = ^(gray_sync_2_reg >> k)."""
    v = gray >> k
    p = 0
    while v:
        p ^= v & 1
        v >>= 1
    return p


def _parity12(v):
    p = 0
    while v:
        p ^= v & 1
        v >>= 1
    return p


def _ctldup_shift(raw, sh):
    """{2{raw}} >> sh, truncated to 2 bits (raw = 2-bit int)."""
    dbl = raw | (raw << SEG_CNT_INT)
    return (dbl >> sh) & ((1 << SEG_CNT_INT) - 1)


class Enc:
    """Cycle-accurate mirror of axi_vfifo_enc."""

    def __init__(self):
        self.reset()

    def reset(self):
        self.input_fifo_wr_ptr = 0      # 7 bits
        self.input_fifo_rd_ptr = 0
        self.hdr_fifo_wr_ptr = 0
        self.hdr_fifo_rd_ptr = 0
        self.mem_rd_data_valid = [0, 0]
        self.hdr_mem_rd_data_valid = 0
        self.seg_mem_wr_addr = [0, 0]   # 5 bits each
        self.seg_mem_rd_addr = [0, 0]
        self.seg_mem = [[0] * 32, [0] * 32]
        self.rd_data = [0, 0]           # 32b mem-read data regs
        self.hdr_mem_len = [0] * 64
        self.hdr_mem_last = [0] * 64
        self.hdr_mem_meta = [0] * 64
        self.hdr_mem_rd_len = 0
        self.hdr_mem_rd_last = 0
        self.hdr_mem_rd_meta = 0
        self.hdr_mem_rd_addr = 0
        self.input_fifo_full = 0
        self.input_fifo_half_full = 0
        self.input_fifo_empty = 1
        self.input_fifo_count = 0
        self.hdr_fifo_full = 0
        self.hdr_fifo_half_full = 0
        self.hdr_fifo_empty = 1
        self.hdr_fifo_count = 0
        self.output_data = 0            # 64 bits
        self.output_valid = [0, 0]
        self.frame = 0
        self.len = 0                    # 12 bits
        self.cycle_valid = 0
        self.cycle_last = 0
        self.cycle_len = 0              # 3 bits
        self.cycle_meta = 0
        self.hdr_len = 0
        self.hdr_meta = 0
        self.hdr_last = 0
        self.hdr_commit = 0
        self.hdr_commit_prev = 0
        self.hdr_valid = 0
        self.out_frame = 0
        self.out_len = 0
        self.out_split1 = 0
        self.out_seg_cnt_in = 0         # 10 bits
        self.out_seg_last_straddle = 0
        self.out_seg_offset = 0         # 1 bit
        self.out_seg_fifo_offset = 0    # 1 bit
        self.out_seg_count = 0
        self.out_hdr = 0                # 24 bits
        self.out_ctl_seg_hdr = 0        # 2 bits
        self.out_ctl_seg_split1 = 0
        self.out_ctl_seg_en = 0
        self.out_ctl_seg_idx = [0, 0]
        self.out_ctl_seg_offset = 0
        self.out_shift = 0              # 24 bits
        self.block_timeout_count = 0
        self.block_timeout = 0

    def tready(self, fifo_rst_in):
        return 1 if (not self.input_fifo_full and not self.hdr_fifo_full and
                     not fifo_rst_in) else 0

    def comb(self, s_tvalid, s_tdata, s_tkeep, s_tlast, s_meta,
             fifo_rst_in, fifo_watermark_in):
        """Port of the encoder's two combinational always blocks."""
        s_tready = self.tready(fifo_rst_in)

        # ---- split input segments ----
        int_seg_valid = [0] * AXIS_SEG_CNT
        if s_tvalid:
            if s_tlast:
                for si in range(AXIS_SEG_CNT):
                    int_seg_valid[si] = 1 if \
                        (s_tkeep >> (SEG_BYTE_LANES * si)) & \
                        ((1 << SEG_BYTE_LANES) - 1) else 0
            else:
                int_seg_valid = [1] * AXIS_SEG_CNT

        # ---- write logic ----
        iwptr_n = self.input_fifo_wr_ptr
        hwptr_n = self.hdr_fifo_wr_ptr

        cycle_len = 0
        for k in range(AXIS_BYTE_LANES):
            cycle_len += (s_tkeep >> k) & 1

        seg_mem_wr_valid = [0] * SEG_CNT_INT
        seg_mem_wr_sel = [0] * SEG_CNT_INT
        cur_seg = self.input_fifo_wr_ptr & SEG_IDX_MASK
        seg_count = 0
        for seg in range(AXIS_SEG_CNT):
            if int_seg_valid[seg]:
                seg_mem_wr_valid[cur_seg] = 1
                seg_mem_wr_sel[cur_seg] = seg
                cur_seg = (cur_seg + 1) & SEG_IDX_MASK
                seg_count += 1

        seg_mem_wr_data = [0] * SEG_CNT_INT
        for seg in range(SEG_CNT_INT):
            sel = seg_mem_wr_sel[seg]
            seg_mem_wr_data[seg] = (s_tdata >> (sel * SEG_WIDTH)) & 0xFFFFFFFF

        seg_mem_wr_addr_n = list(self.seg_mem_wr_addr)
        seg_mem_wr_en = [0] * SEG_CNT_INT

        hdr_mem_wr_len = self.hdr_len
        hdr_mem_wr_last = self.hdr_last
        hdr_mem_wr_meta = self.hdr_meta
        hdr_mem_wr_addr = self.hdr_fifo_wr_ptr
        hdr_mem_wr_en = 0

        frame_n = self.frame
        len_n = self.len
        cycle_valid_n = 0
        cycle_last_n = self.cycle_last
        cycle_len_n = self.cycle_len
        cycle_meta_n = self.cycle_meta

        hdr_len_n = self.len
        hdr_meta_n = self.cycle_meta
        hdr_last_n = self.cycle_last
        hdr_commit_n = 0
        hdr_commit_prev_n = 0
        hdr_valid_n = 0

        if s_tvalid and s_tready:
            seg_mem_wr_en = list(seg_mem_wr_valid)
            iwptr_n = (self.input_fifo_wr_ptr + seg_count) & 0x7F
            for seg in range(SEG_CNT_INT):
                seg_mem_wr_addr_n[seg] = \
                    ((iwptr_n + (SEG_CNT_INT - 1 - seg)) >> SEG_IDX_WIDTH) \
                    & 0x1F
            cycle_valid_n = 1
            cycle_last_n = s_tlast
            cycle_len_n = cycle_len
            cycle_meta_n = s_meta

        if self.cycle_valid:
            if not self.frame:
                frame_n = 1
                if self.cycle_last:
                    len_n = self.cycle_len
                else:
                    len_n = AXIS_BYTE_LANES
                hdr_len_n = (len_n - 1) & 0xFFF
                hdr_meta_n = self.cycle_meta
                hdr_last_n = self.cycle_last
                hdr_valid_n = 1
                if self.cycle_last:
                    hdr_commit_n = 1
                    frame_n = 0
            else:
                if self.cycle_meta != self.hdr_meta:
                    if self.cycle_last:
                        len_n = self.cycle_len
                    else:
                        len_n = AXIS_BYTE_LANES
                else:
                    if self.cycle_last:
                        len_n = (self.len + self.cycle_len) & 0xFFF
                    else:
                        len_n = (self.len + AXIS_BYTE_LANES) & 0xFFF
                hdr_len_n = (len_n - 1) & 0xFFF
                hdr_meta_n = self.cycle_meta
                hdr_last_n = self.cycle_last
                hdr_valid_n = 1
                if self.cycle_meta != self.hdr_meta:
                    hdr_commit_prev_n = 1
                    if self.cycle_last:
                        hdr_commit_n = 1
                        frame_n = 0
                elif self.cycle_last or len_n >= MAX_BLOCK_LEN:
                    hdr_commit_n = 1
                    frame_n = 0

        if self.hdr_valid:
            hdr_mem_wr_len = self.hdr_len
            hdr_mem_wr_last = self.hdr_last
            hdr_mem_wr_meta = self.hdr_meta
            hdr_mem_wr_addr = self.hdr_fifo_wr_ptr
            hdr_mem_wr_en = 1
            if self.hdr_commit_prev:
                if self.hdr_commit:
                    hwptr_n = (self.hdr_fifo_wr_ptr + 2) & 0x7F
                    hdr_mem_wr_addr = (self.hdr_fifo_wr_ptr + 1) & 0x7F
                else:
                    hwptr_n = (self.hdr_fifo_wr_ptr + 1) & 0x7F
                    hdr_mem_wr_addr = (self.hdr_fifo_wr_ptr + 1) & 0x7F
            else:
                if self.hdr_commit:
                    hwptr_n = (self.hdr_fifo_wr_ptr + 1) & 0x7F
                    hdr_mem_wr_addr = self.hdr_fifo_wr_ptr

        # ---- read logic ----
        irptr_n = self.input_fifo_rd_ptr
        hrptr_n = self.hdr_fifo_rd_ptr

        mem_rd_data_valid_n = list(self.mem_rd_data_valid)
        hdr_mem_rd_data_valid_n = self.hdr_mem_rd_data_valid

        output_data_n = self.output_data
        output_valid_n = [0, 0]

        seg_mem_rd_addr_n = list(self.seg_mem_rd_addr)
        seg_mem_rd_en = [0, 0]

        hdr_mem_rd_addr_n = self.hdr_mem_rd_addr
        hdr_mem_rd_en = 0

        out_frame_n = self.out_frame
        out_len_n = self.out_len
        out_split1_n = self.out_split1
        out_seg_cnt_in_n = self.out_seg_cnt_in
        out_seg_last_straddle_n = self.out_seg_last_straddle
        out_seg_offset_n = self.out_seg_offset
        out_seg_fifo_offset_n = self.out_seg_fifo_offset

        out_hdr_n = self.out_hdr

        out_ctl_seg_hdr_raw = 0
        out_ctl_seg_hdr_n = 0
        out_ctl_seg_split1_raw = 0
        out_ctl_seg_split1_n = 0
        out_ctl_seg_en_raw = 0
        out_ctl_seg_en_n = 0
        out_ctl_seg_offset_n = self.out_seg_offset

        out_ctl_seg_idx_n = [0, 0]
        for seg in range(SEG_CNT_INT):
            out_ctl_seg_idx_n[seg] = \
                (self.out_seg_fifo_offset - self.out_seg_offset + seg) & \
                SEG_IDX_MASK

        # partial block timeout handling
        block_timeout_count_n = self.block_timeout_count
        block_timeout_n = 1 if self.block_timeout_count == 0 else 0
        if (self.output_valid[0] or self.output_valid[1]) or \
                self.out_seg_offset == 0:
            block_timeout_count_n = 0xFF
            block_timeout_n = 0
        elif self.block_timeout_count > 0:
            block_timeout_count_n = (self.block_timeout_count - 1) & 0xFF

        # process headers and generate output commands
        if not fifo_watermark_in:
            if self.out_frame:
                if out_seg_cnt_in_n >= SEG_CNT_INT:
                    out_frame_n = 1 if (out_seg_last_straddle_n or
                                        out_seg_cnt_in_n > SEG_CNT_INT) \
                        else 0
                    out_ctl_seg_en_raw = (1 << SEG_CNT_INT) - 1
                    out_seg_offset_n = \
                        (self.out_seg_offset + SEG_CNT_INT) & SEG_IDX_MASK
                    out_seg_fifo_offset_n = \
                        (self.out_seg_fifo_offset + SEG_CNT_INT) & SEG_IDX_MASK
                else:
                    out_frame_n = 0
                    if out_seg_last_straddle_n:
                        out_ctl_seg_split1_raw = 1 << out_seg_cnt_in_n
                        if out_seg_cnt_in_n == SEG_CNT_INT - 1:
                            out_ctl_seg_en_raw = (1 << SEG_CNT_INT) - 1
                        else:
                            out_ctl_seg_en_raw = \
                                ((1 << SEG_CNT_INT) - 1) >> \
                                (SEG_CNT_INT - (out_seg_cnt_in_n + 1))
                        out_seg_offset_n = \
                            (self.out_seg_offset + out_seg_cnt_in_n + 1) & \
                            SEG_IDX_MASK
                    else:
                        out_ctl_seg_en_raw = ((1 << SEG_CNT_INT) - 1) >> \
                            (SEG_CNT_INT - out_seg_cnt_in_n)
                        out_seg_offset_n = \
                            (self.out_seg_offset + out_seg_cnt_in_n) & \
                            SEG_IDX_MASK
                    out_seg_fifo_offset_n = \
                        (self.out_seg_fifo_offset + out_seg_cnt_in_n) & \
                        SEG_IDX_MASK
                out_seg_cnt_in_n = (out_seg_cnt_in_n - SEG_CNT_INT) & 0x3FF
            else:
                out_len_n = self.hdr_mem_rd_len
                out_seg_cnt_in_n = ((self.hdr_mem_rd_len + SEG_BYTE_LANES)
                                    >> SEG_BYTE_IDX_WIDTH) & 0x3FF
                out_seg_last_straddle_n = 1 if \
                    (((self.hdr_mem_rd_len & (SEG_BYTE_LANES - 1)) +
                      HDR_SIZE) >> SEG_BYTE_IDX_WIDTH) != 0 else 0
                out_hdr_n = 0
                out_hdr_n |= 1 << 0
                out_hdr_n |= (1 if self.hdr_mem_rd_last else 0) << 1
                out_hdr_n |= (0 if self.hdr_mem_rd_last else 1) << 2
                out_hdr_n |= self.hdr_mem_rd_len << 4
                out_hdr_n |= _parity12(self.hdr_mem_rd_len) << 3
                if META_WIDTH > 0:
                    out_hdr_n |= self.hdr_mem_rd_meta << 16
                out_hdr_n &= 0xFFFFFF

                out_ctl_seg_hdr_raw = 1

                if self.hdr_mem_rd_data_valid:
                    if out_seg_cnt_in_n >= SEG_CNT_INT:
                        # RTL: out_frame_next = out_seg_last_straddle_next ||
                        #       out_seg_cnt_in_next > SEG_CNT_INT  (NEW straddle)
                        out_frame_n = 1 if (out_seg_last_straddle_n or
                                            out_seg_cnt_in_n > SEG_CNT_INT) \
                            else 0
                        out_ctl_seg_en_raw = (1 << SEG_CNT_INT) - 1
                        out_seg_offset_n = \
                            (self.out_seg_offset + SEG_CNT_INT) & SEG_IDX_MASK
                        out_seg_fifo_offset_n = \
                            (self.out_seg_fifo_offset + SEG_CNT_INT) & \
                            SEG_IDX_MASK
                    else:
                        out_frame_n = 0
                        if out_seg_last_straddle_n:
                            out_ctl_seg_split1_raw = 1 << out_seg_cnt_in_n
                            if out_seg_cnt_in_n == SEG_CNT_INT - 1:
                                out_ctl_seg_en_raw = (1 << SEG_CNT_INT) - 1
                            else:
                                out_ctl_seg_en_raw = \
                                    ((1 << SEG_CNT_INT) - 1) >> \
                                    (SEG_CNT_INT - (out_seg_cnt_in_n + 1))
                            out_seg_offset_n = \
                                (self.out_seg_offset + out_seg_cnt_in_n + 1) \
                                & SEG_IDX_MASK
                        else:
                            out_ctl_seg_en_raw = \
                                ((1 << SEG_CNT_INT) - 1) >> \
                                (SEG_CNT_INT - out_seg_cnt_in_n)
                            out_seg_offset_n = \
                                (self.out_seg_offset + out_seg_cnt_in_n) & \
                                SEG_IDX_MASK
                        out_seg_fifo_offset_n = \
                            (self.out_seg_fifo_offset + out_seg_cnt_in_n) & \
                            SEG_IDX_MASK
                    out_seg_cnt_in_n = (out_seg_cnt_in_n - SEG_CNT_INT) & 0x3FF
                    hdr_mem_rd_data_valid_n = 0
                elif self.block_timeout and self.out_seg_offset:
                    # insert padding
                    out_hdr_n = out_hdr_n & ~0xFFFF
                    out_ctl_seg_en_raw = ((1 << SEG_CNT_INT) - 1) >> \
                        self.out_seg_offset
                    out_ctl_seg_hdr_raw = (1 << SEG_CNT_INT) - 1
                    out_ctl_seg_split1_raw = (1 << SEG_CNT_INT) - 1
                    out_seg_offset_n = 0

        # shift ctl masks: {2{raw}} >> (SEG_CNT_INT - out_seg_offset_reg)
        sh = SEG_CNT_INT - self.out_seg_offset
        out_ctl_seg_hdr_n = _ctldup_shift(out_ctl_seg_hdr_raw, sh)
        out_ctl_seg_split1_n = _ctldup_shift(out_ctl_seg_split1_raw, sh)
        out_ctl_seg_en_n = _ctldup_shift(out_ctl_seg_en_raw, sh)

        out_shift_n = self.out_shift

        # mux segments (uses the PRE-EDGE ctl registers, like the RTL)
        cur_rd_seg = self.out_ctl_seg_offset
        for rd_seg in range(SEG_CNT_INT):
            word_off = cur_rd_seg * SEG_WIDTH
            # output_data_next[word +: 32] = out_shift_next (zero-extended)
            output_data_n = (output_data_n & ~(0xFFFFFFFF << word_off)) | \
                ((out_shift_n & 0xFFFFFF) << word_off)
            # output_data_next[word+24 +: 8] = rd_data[sel][0+:8]
            sel = self.out_ctl_seg_idx[cur_rd_seg]
            mbyte = self.rd_data[sel] & 0xFF
            output_data_n = (output_data_n & ~(0xFF << (word_off + 24))) | \
                (mbyte << (word_off + 24))
            if (self.out_ctl_seg_hdr >> cur_rd_seg) & 1:
                output_data_n = (output_data_n &
                                 ~(0xFFFFFF << word_off)) | \
                    ((self.out_hdr & 0xFFFFFF) << word_off)
            output_valid_n[cur_rd_seg] = (self.out_ctl_seg_en >> cur_rd_seg) \
                & 1
            if ((self.out_ctl_seg_en >> cur_rd_seg) & 1) and \
                    not ((self.out_ctl_seg_split1 >> cur_rd_seg) & 1):
                mem_rd_data_valid_n[sel] = 0
            if (self.out_ctl_seg_en >> cur_rd_seg) & 1:
                # RTL: (idx+1)*SEG_WIDTH-HDR_WIDTH = idx*SEG_WIDTH+8
                # -> bits 8..31 of the CURRENT segment
                out_shift_n = (self.rd_data[sel] >> 8) & 0xFFFFFF
            cur_rd_seg = (cur_rd_seg + 1) & SEG_IDX_MASK

        # read segments
        cur_rd_seg = self.input_fifo_rd_ptr & SEG_IDX_MASK
        rd_valid = 1
        for rd_seg in range(SEG_CNT_INT):
            if not mem_rd_data_valid_n[cur_rd_seg] and \
                    self.input_fifo_count > rd_seg and rd_valid:
                irptr_n = (self.input_fifo_rd_ptr + rd_seg + 1) & 0x7F
                seg_mem_rd_en[cur_rd_seg] = 1
                seg_mem_rd_addr_n[cur_rd_seg] = \
                    (((self.input_fifo_rd_ptr + rd_seg) >> SEG_IDX_WIDTH)
                     + 1) & 0x1F
                mem_rd_data_valid_n[cur_rd_seg] = 1
            else:
                rd_valid = 0
            cur_rd_seg = (cur_rd_seg + 1) & SEG_IDX_MASK

        # read header
        if not hdr_mem_rd_data_valid_n and not self.hdr_fifo_empty:
            hrptr_n = (self.hdr_fifo_rd_ptr + 1) & 0x7F
            hdr_mem_rd_en = 1
            hdr_mem_rd_addr_n = hrptr_n
            hdr_mem_rd_data_valid_n = 1

        self._n = {
            "iwptr": iwptr_n, "irptr": irptr_n,
            "hwptr": hwptr_n, "hrptr": hrptr_n,
            "seg_mem_wr_addr": seg_mem_wr_addr_n,
            "seg_mem_wr_en": seg_mem_wr_en,
            "seg_mem_wr_data": seg_mem_wr_data,
            "hdr_mem_wr_len": hdr_mem_wr_len,
            "hdr_mem_wr_last": hdr_mem_wr_last,
            "hdr_mem_wr_meta": hdr_mem_wr_meta,
            "hdr_mem_wr_addr": hdr_mem_wr_addr,
            "hdr_mem_wr_en": hdr_mem_wr_en,
            "frame": frame_n, "len": len_n,
            "cycle_valid": cycle_valid_n, "cycle_last": cycle_last_n,
            "cycle_len": cycle_len_n, "cycle_meta": cycle_meta_n,
            "hdr_len": hdr_len_n, "hdr_meta": hdr_meta_n,
            "hdr_last": hdr_last_n, "hdr_commit": hdr_commit_n,
            "hdr_commit_prev": hdr_commit_prev_n, "hdr_valid": hdr_valid_n,
            "seg_mem_rd_addr": seg_mem_rd_addr_n,
            "seg_mem_rd_en": seg_mem_rd_en,
            "hdr_mem_rd_addr": hdr_mem_rd_addr_n,
            "hdr_mem_rd_en": hdr_mem_rd_en,
            "mem_rd_data_valid": mem_rd_data_valid_n,
            "hdr_mem_rd_data_valid": hdr_mem_rd_data_valid_n,
            "out_frame": out_frame_n, "out_len": out_len_n,
            "out_split1": out_split1_n,
            "out_seg_cnt_in": out_seg_cnt_in_n,
            "out_seg_last_straddle": out_seg_last_straddle_n,
            "out_seg_offset": out_seg_offset_n,
            "out_seg_fifo_offset": out_seg_fifo_offset_n,
            "out_hdr": out_hdr_n,
            "out_ctl_seg_hdr": out_ctl_seg_hdr_n,
            "out_ctl_seg_split1": out_ctl_seg_split1_n,
            "out_ctl_seg_en": out_ctl_seg_en_n,
            "out_ctl_seg_idx": out_ctl_seg_idx_n,
            "out_ctl_seg_offset": out_ctl_seg_offset_n,
            "out_shift": out_shift_n,
            "block_timeout_count": block_timeout_count_n,
            "block_timeout": block_timeout_n,
            "output_data": output_data_n,
            "output_valid": output_valid_n,
        }
        return {
            "tready": s_tready,
            "output_data": output_data_n,
            "output_valid": output_valid_n,
        }

    def edge(self, rst, fifo_rst_in):
        n = self._n
        # limits (pre-edge pointers)
        self.input_fifo_full = 1 if \
            ((self.input_fifo_wr_ptr - self.input_fifo_rd_ptr) & 0x7F) >= \
            (2 ** INPUT_FIFO_ADDR_WIDTH * SEG_CNT_INT) - SEG_CNT_INT * 2 \
            else 0
        self.input_fifo_half_full = 1 if \
            ((self.input_fifo_wr_ptr - self.input_fifo_rd_ptr) & 0x7F) >= \
            (2 ** INPUT_FIFO_ADDR_WIDTH * SEG_CNT_INT) // 2 else 0
        self.hdr_fifo_full = 1 if \
            ((self.hdr_fifo_wr_ptr - self.hdr_fifo_rd_ptr) & 0x7F) >= \
            2 ** HDR_FIFO_ADDR_WIDTH - 4 else 0
        self.hdr_fifo_half_full = 1 if \
            ((self.hdr_fifo_wr_ptr - self.hdr_fifo_rd_ptr) & 0x7F) >= \
            2 ** HDR_FIFO_ADDR_WIDTH // 2 else 0

        # segment memory writes (pre-edge comb values)
        for seg in range(SEG_CNT_INT):
            if n["seg_mem_wr_en"][seg]:
                self.seg_mem[seg][self.seg_mem_wr_addr[seg] & 0x1F] = \
                    n["seg_mem_wr_data"][seg] & 0xFFFFFFFF
        # header memory writes
        if n["hdr_mem_wr_en"]:
            self.hdr_mem_len[n["hdr_mem_wr_addr"] & 0x3F] = \
                n["hdr_mem_wr_len"] & 0xFFF
            self.hdr_mem_last[n["hdr_mem_wr_addr"] & 0x3F] = \
                n["hdr_mem_wr_last"]
            self.hdr_mem_meta[n["hdr_mem_wr_addr"] & 0x3F] = \
                n["hdr_mem_wr_meta"]
        # segment memory reads (pre-edge addr regs)
        for seg in range(SEG_CNT_INT):
            if n["seg_mem_rd_en"][seg]:
                self.rd_data[seg] = \
                    self.seg_mem[seg][self.seg_mem_rd_addr[seg] & 0x1F]
        # header memory read
        if n["hdr_mem_rd_en"]:
            self.hdr_mem_rd_len = \
                self.hdr_mem_len[self.hdr_mem_rd_addr & 0x3F]
            self.hdr_mem_rd_last = \
                self.hdr_mem_last[self.hdr_mem_rd_addr & 0x3F]
            self.hdr_mem_rd_meta = \
                self.hdr_mem_meta[self.hdr_mem_rd_addr & 0x3F]

        self.input_fifo_wr_ptr = n["iwptr"]
        self.input_fifo_rd_ptr = n["irptr"]
        self.hdr_fifo_wr_ptr = n["hwptr"]
        self.hdr_fifo_rd_ptr = n["hrptr"]
        self.seg_mem_wr_addr = list(n["seg_mem_wr_addr"])
        self.seg_mem_rd_addr = list(n["seg_mem_rd_addr"])
        self.frame = n["frame"]
        self.len = n["len"]
        self.cycle_valid = n["cycle_valid"]
        self.cycle_last = n["cycle_last"]
        self.cycle_len = n["cycle_len"]
        self.cycle_meta = n["cycle_meta"]
        self.hdr_len = n["hdr_len"]
        self.hdr_meta = n["hdr_meta"]
        self.hdr_last = n["hdr_last"]
        self.hdr_commit = n["hdr_commit"]
        self.hdr_commit_prev = n["hdr_commit_prev"]
        self.hdr_valid = n["hdr_valid"]
        self.mem_rd_data_valid = list(n["mem_rd_data_valid"])
        self.hdr_mem_rd_data_valid = n["hdr_mem_rd_data_valid"]
        self.hdr_mem_rd_addr = n["hdr_mem_rd_addr"] & 0x3F
        self.output_data = n["output_data"]
        self.output_valid = list(n["output_valid"])
        self.out_frame = n["out_frame"]
        self.out_len = n["out_len"]
        self.out_split1 = n["out_split1"]
        self.out_seg_cnt_in = n["out_seg_cnt_in"]
        self.out_seg_last_straddle = n["out_seg_last_straddle"]
        self.out_seg_offset = n["out_seg_offset"]
        self.out_seg_fifo_offset = n["out_seg_fifo_offset"]
        self.out_hdr = n["out_hdr"]
        self.out_ctl_seg_hdr = n["out_ctl_seg_hdr"]
        self.out_ctl_seg_split1 = n["out_ctl_seg_split1"]
        self.out_ctl_seg_en = n["out_ctl_seg_en"]
        self.out_ctl_seg_idx = list(n["out_ctl_seg_idx"])
        self.out_ctl_seg_offset = n["out_ctl_seg_offset"]
        self.out_shift = n["out_shift"]
        self.block_timeout_count = n["block_timeout_count"]
        self.block_timeout = n["block_timeout"]

        self.input_fifo_count = (n["iwptr"] - n["irptr"]) & 0x7F
        self.input_fifo_empty = 1 if n["iwptr"] == n["irptr"] else 0
        self.hdr_fifo_count = (n["hwptr"] - n["hrptr"]) & 0x7F
        self.hdr_fifo_empty = 1 if n["hwptr"] == n["hrptr"] else 0

        if rst or fifo_rst_in:
            self.input_fifo_wr_ptr = 0
            self.hdr_fifo_wr_ptr = 0
            self.seg_mem_wr_addr = [0, 0]
            self.frame = 0
            self.cycle_valid = 0
            self.hdr_valid = 0
            self.input_fifo_rd_ptr = 0
            self.input_fifo_count = 0
            self.input_fifo_empty = 1
            self.hdr_fifo_rd_ptr = 0
            self.hdr_fifo_count = 0
            self.hdr_fifo_empty = 1
            self.seg_mem_rd_addr = [0, 0]
            self.hdr_mem_rd_addr = 0
            self.mem_rd_data_valid = [0, 0]
            self.hdr_mem_rd_data_valid = 0
            self.out_frame = 0
            self.out_len = 0
            self.out_split1 = 0
            self.out_seg_offset = 0
            self.out_seg_fifo_offset = 0
            self.out_seg_count = 0
            self.input_fifo_full = 0
            self.input_fifo_half_full = 0
            self.hdr_fifo_full = 0
            self.hdr_fifo_half_full = 0
        self._n = None


class RawWr:
    """Cycle-accurate mirror of axi_vfifo_raw_wr (SEG_CNT=1, SEG_WIDTH=32,
    WRITE_FIFO_DEPTH=64, AXI_MAX_BURST_LEN=16, LEN_WIDTH=16)."""

    def __init__(self):
        self.reset()

    def reset(self):
        # async reset sync chain (input_clk domain; rst_req_int = cfg_reset)
        self.rst_sync_1 = 1
        self.rst_sync_2 = 1
        self.rst_sync_3 = 1
        self._rst_req_prev = 0
        # AXI master regs
        self.awaddr = 0
        self.awlen = 0
        self.awvalid = 0
        self.wdata = 0
        self.wstrb = 0
        self.wlast = 0
        self.wvalid = 0
        self.bready = 0
        # input datapath
        self.input_valid_int = 0
        # write fifo pointers
        self.rd_ptr = 0
        self.rd_ptr_gray = 0
        self.wr_ptr_gray_sync_1 = 0
        self.wr_ptr_gray_sync_2 = 0
        self.wr_ptr_sync = 0
        self.rd_ptr_gray_sync_1 = 0
        self.rd_ptr_gray_sync_2 = 0
        self.rd_ptr_sync = 0
        self.occupancy = 0
        # per-seg
        self.seg_wr_ptr = 0
        self.seg_wr_ptr_gray = 0
        self.seg_occupancy = 0
        self.seg_mem = [0] * 64
        self.seg_rd_data = 0
        # burst engine
        self.wr_burst = 0
        self.wr_burst_len = 0
        self.wr_timeout_count = 0
        self.wr_timeout = 0
        self.fifo_full_wr_blk_adj = 0
        self.wr_start_ptr = 0        # 17 bits
        self.wr_start_ptr_blk_adj = 0
        self.wr_finish_ptr = 0
        # resp fifo
        self.resp_fifo_we = 0
        self.resp_fifo_wr_ptr = 0
        self.resp_fifo_rd_ptr = 0
        self.resp_fifo_burst_len = [0] * 32
        self.resp_fifo_wr_burst_len = 0

    def comb(self, input_valid, input_data, awready, wready, bvalid,
             cfg_base_addr, cfg_size_mask, cfg_enable, cfg_reset,
             input_rst, rd_finish_ptr_in):
        """Port of the write-logic comb block + per-seg ready."""
        # per-seg ready (input_clk domain)
        seg_full = 1 if self.seg_wr_ptr_gray == \
            ((self.rd_ptr_gray_sync_2 ^ 0x60) & 0x7F) else 0
        input_ready = 1 if (not seg_full and not self.rst_sync_3) else 0
        seg_empty = 1 if self.rd_ptr == self.wr_ptr_sync else 0
        seg_watermark = 1 if self.seg_occupancy > WATERMARK_LEVEL else 0
        input_watermark = 1 if (seg_watermark or self.rst_sync_3) else 0
        write_fifo_empty = seg_empty
        input_data_int = self.seg_rd_data

        # ---- write logic comb ----
        wr_start_ptr_next = self.wr_start_ptr
        wr_start_ptr_blk_adj_next = self.wr_start_ptr_blk_adj
        wr_finish_ptr_next = self.wr_finish_ptr

        wr_burst_next = self.wr_burst
        wr_burst_len_next = self.wr_burst_len
        wr_timeout_count_next = self.wr_timeout_count
        wr_timeout_next = self.wr_timeout

        # FIFO full (block adjusted)
        occ_blk = (self.wr_start_ptr_blk_adj - rd_finish_ptr_in) & 0x1FFFF
        fifo_full_wr_blk_adj = 1 if ((occ_blk & ~cfg_size_mask) or
                                     (((~occ_blk & cfg_size_mask &
                                        ~WRITE_BURST_ADDR_MASK) &
                                       0x1FFFF) == 0 and
                                      (occ_blk & WRITE_BURST_ADDR_MASK))) \
            else 0
        fifo_full_wr_blk_adj_next = fifo_full_wr_blk_adj

        resp_fifo_we_next = 0
        resp_fifo_rd_ptr_next = self.resp_fifo_rd_ptr
        resp_fifo_wr_burst_len_next = self.wr_burst_len

        input_read_en = 0

        awaddr_next = self.awaddr
        awlen_next = self.awlen
        awvalid_next = 1 if (self.awvalid and not awready) else 0

        wdata_next = self.wdata
        wstrb_next = self.wstrb
        wlast_next = self.wlast
        wvalid_next = 1 if (self.wvalid and not wready) else 0

        bready_next = 0

        # partial burst timeout handling
        wr_timeout_next = 1 if self.wr_timeout_count == 0 else 0
        if not self.input_valid_int or self.awvalid:
            wr_timeout_count_next = 0xFF
            wr_timeout_next = 0
        elif self.wr_timeout_count > 0:
            wr_timeout_count_next = (self.wr_timeout_count - 1) & 0xFF

        # compute length based on input FIFO occupancy
        occ = self.occupancy
        if ((((self.wr_start_ptr & WRITE_BURST_ADDR_MASK) >>
              AXI_BURST_SIZE) + occ) >> WRITE_BURST_LEN_WIDTH) != 0:
            # crosses burst boundary, write up to burst boundary
            wr_burst_len = WRITE_MAX_BURST_LEN_INT - 1 - \
                ((self.wr_start_ptr & WRITE_BURST_ADDR_MASK) >>
                 AXI_BURST_SIZE)
            wr_start_ptr = ((self.wr_start_ptr & ~WRITE_BURST_ADDR_MASK) +
                            (1 << WRITE_BURST_ADDR_WIDTH)) & 0x1FFFF
            wr_start_ptr_blk_adj = wr_start_ptr
        else:
            # does not cross burst boundary, write available data
            # NOTE: the len reg is WRITE_BURST_LEN_WIDTH(4) bits -> truncates
            wr_burst_len = (occ - 1) & 0xF
            wr_start_ptr = (self.wr_start_ptr + (occ << AXI_BURST_SIZE)) & \
                0x1FFFF
            wr_start_ptr_blk_adj = \
                ((self.wr_start_ptr & ~WRITE_BURST_ADDR_MASK) +
                 (1 << WRITE_BURST_ADDR_WIDTH)) & 0x1FFFF

        resp_fifo_wr_burst_len_next = wr_burst_len

        # generate AXI write bursts
        if not self.awvalid and not self.wr_burst:
            wr_burst_len_next = wr_burst_len
            awaddr_next = (cfg_base_addr +
                           (self.wr_start_ptr & cfg_size_mask)) & 0xFFFF
            awlen_next = wr_burst_len & 0xFF
            if cfg_enable and self.input_valid_int and \
                    not self.fifo_full_wr_blk_adj:
                if (occ >> WRITE_BURST_LEN_WIDTH) != 0 or self.wr_timeout:
                    wr_burst_next = 1
                    awvalid_next = 1
                    resp_fifo_we_next = 1
                    wr_start_ptr_next = wr_start_ptr
                    wr_start_ptr_blk_adj_next = wr_start_ptr_blk_adj

        # transfer data
        if not self.wvalid or wready:
            wdata_next = input_data_int
            wlast_next = 1 if self.wr_burst_len == 0 else 0
            if self.wr_burst:
                wstrb_next = 0xF
                if cfg_reset:
                    wstrb_next = 0
                    wvalid_next = 1
                    wr_burst_len_next = (self.wr_burst_len - 1) & 0xF
                    wr_burst_next = 1 if self.wr_burst_len != 0 else 0
                elif self.input_valid_int:
                    input_read_en = 1
                    wvalid_next = 1
                    wr_burst_len_next = (self.wr_burst_len - 1) & 0xF
                    wr_burst_next = 1 if self.wr_burst_len != 0 else 0

        # handle AXI write completions
        bready_next = 1
        if bvalid:
            wr_finish_ptr_next = (self.wr_finish_ptr +
                                  ((self.resp_fifo_burst_len[
                                      self.resp_fifo_rd_ptr & 0x1F] + 1)
                                   << AXI_BURST_SIZE)) & 0x1FFFF
            resp_fifo_rd_ptr_next = (self.resp_fifo_rd_ptr + 1) & 0x7F

        if cfg_reset:
            wr_start_ptr_next = 0
            wr_start_ptr_blk_adj_next = 0
            wr_finish_ptr_next = 0

        self._n = {
            "input_ready": input_ready,
            "input_watermark": input_watermark,
            "wr_start_ptr": wr_start_ptr_next,
            "wr_start_ptr_blk_adj": wr_start_ptr_blk_adj_next,
            "wr_finish_ptr": wr_finish_ptr_next,
            "wr_burst": wr_burst_next,
            "wr_burst_len": wr_burst_len_next,
            "wr_timeout_count": wr_timeout_count_next,
            "wr_timeout": wr_timeout_next,
            "fifo_full_wr_blk_adj": fifo_full_wr_blk_adj_next,
            "resp_fifo_we": resp_fifo_we_next,
            "resp_fifo_rd_ptr": resp_fifo_rd_ptr_next,
            "resp_fifo_wr_burst_len": resp_fifo_wr_burst_len_next,
            "input_read_en": input_read_en,
            "awaddr": awaddr_next, "awlen": awlen_next,
            "awvalid": awvalid_next,
            "wdata": wdata_next, "wstrb": wstrb_next,
            "wlast": wlast_next, "wvalid": wvalid_next,
            "bready": bready_next,
        }
        return {
            "input_ready": input_ready,
            "input_watermark": input_watermark,
            "awvalid": self.awvalid,
            "wvalid": self.wvalid,
            "wlast": self.wlast,
            "bready": bready_next,
            "sts_fifo_occupancy": (self.wr_start_ptr -
                                   rd_finish_ptr_in) & 0x1FFFF,
            "sts_fifo_empty": 1 if self.wr_start_ptr == rd_finish_ptr_in
            else 0,
            "sts_fifo_full": self.fifo_full_wr_blk_adj,
            "sts_write_active": 1 if (self.wr_burst or self.resp_fifo_we or
                                      (self.resp_fifo_wr_ptr !=
                                       self.resp_fifo_rd_ptr)) else 0,
        }

    def edge(self, input_valid, input_data, rst, cfg_reset, input_rst,
             cfg_reset_next=0):
        n = self._n
        # pre-edge gray captures (sync chains sample pre-edge values)
        _wr_gray = self.seg_wr_ptr_gray
        _rd_gray = self.rd_ptr_gray
        # pre-edge rst_sync_3 (reset conditions sample it pre-edge)
        _rst3_pre = self.rst_sync_3

        # input_clk domain: async rst sync chain
        # (R(t+1) = L(t) | L(t+1) - assert on the rise, hold one extra)
        _r1 = self.rst_sync_1
        _r2 = self.rst_sync_2
        self.rst_sync_1 = 1 if (cfg_reset or cfg_reset_next) else 0
        self.rst_sync_2 = _r1
        self.rst_sync_3 = _r2

        # input_clk domain: seg write + occupancy
        self.seg_occupancy = (self.seg_wr_ptr - self.rd_ptr_sync) & 0x7F
        if n["input_ready"] and input_valid:
            self.seg_mem[self.seg_wr_ptr & 0x3F] = input_data & 0xFFFFFFFF
            nxt = (self.seg_wr_ptr + 1) & 0x7F
            self.seg_wr_ptr = nxt
            self.seg_wr_ptr_gray = nxt ^ (nxt >> 1)
        if input_rst or _rst3_pre:
            self.seg_wr_ptr = 0
            self.seg_wr_ptr_gray = 0

        # clk domain: seg read
        empty = 1 if self.rd_ptr == self.wr_ptr_sync else 0
        if not empty and (not self.input_valid_int or n["input_read_en"]):
            self.seg_rd_data = self.seg_mem[self.rd_ptr & 0x3F]

        # clk domain: read logic (all reads pre-edge)
        _ivi = self.input_valid_int
        _rdp = self.rd_ptr
        self.occupancy = ((self.wr_ptr_sync - _rdp + _ivi) & 0x7F)
        if n["input_read_en"]:
            self.input_valid_int = 0
            self.occupancy = (self.wr_ptr_sync - _rdp) & 0x7F
        if not empty and (not _ivi or n["input_read_en"]):
            self.input_valid_int = 1
            nxt = (_rdp + 1) & 0x7F
            self.rd_ptr = nxt
            self.rd_ptr_gray = nxt ^ (nxt >> 1)
            # NOTE: the RTL uses the PRE-EDGE rd_ptr here
            self.occupancy = (self.wr_ptr_sync - _rdp) & 0x7F
        if rst or cfg_reset:
            self.rd_ptr = 0
            self.rd_ptr_gray = 0
            self.input_valid_int = 0

        # clk domain: write logic regs
        self.wr_start_ptr = n["wr_start_ptr"]
        self.wr_start_ptr_blk_adj = n["wr_start_ptr_blk_adj"]
        self.wr_finish_ptr = n["wr_finish_ptr"]
        self.wr_burst = n["wr_burst"]
        self.wr_burst_len = n["wr_burst_len"]
        self.wr_timeout_count = n["wr_timeout_count"]
        self.wr_timeout = n["wr_timeout"]
        self.fifo_full_wr_blk_adj = n["fifo_full_wr_blk_adj"]
        self.awaddr = n["awaddr"]
        self.awlen = n["awlen"]
        self.awvalid = n["awvalid"]
        self.wdata = n["wdata"]
        self.wstrb = n["wstrb"]
        self.wlast = n["wlast"]
        self.wvalid = n["wvalid"]
        self.bready = n["bready"]
        self.resp_fifo_we = n["resp_fifo_we"]
        self.resp_fifo_wr_burst_len = n["resp_fifo_wr_burst_len"]
        if self.resp_fifo_we:
            self.resp_fifo_burst_len[self.resp_fifo_wr_ptr & 0x1F] = \
                self.resp_fifo_wr_burst_len
            self.resp_fifo_wr_ptr = (self.resp_fifo_wr_ptr + 1) & 0x7F
        self.resp_fifo_rd_ptr = n["resp_fifo_rd_ptr"]
        if rst:
            self.wr_burst = 0
            self.awvalid = 0
            self.wvalid = 0
            self.bready = 0
            self.resp_fifo_we = 0
            self.resp_fifo_wr_ptr = 0
            self.resp_fifo_rd_ptr = 0

        # clk domain: wr ptr gray sync (input_clk -> clk); pre-edge samples
        _s1 = self.wr_ptr_gray_sync_1
        _s2 = self.wr_ptr_gray_sync_2
        self.wr_ptr_gray_sync_1 = _wr_gray
        self.wr_ptr_gray_sync_2 = _s1
        self.wr_ptr_sync = 0
        for k in range(WRITE_FIFO_ADDR_WIDTH + 1):
            self.wr_ptr_sync |= _xor_reduce_shift(_s2, k) << k
        if rst or cfg_reset:
            self.wr_ptr_gray_sync_1 = 0
            self.wr_ptr_gray_sync_2 = 0
            self.wr_ptr_sync = 0

        # input_clk domain: rd ptr gray sync (clk -> input_clk)
        _s1 = self.rd_ptr_gray_sync_1
        _s2 = self.rd_ptr_gray_sync_2
        self.rd_ptr_gray_sync_1 = _rd_gray
        self.rd_ptr_gray_sync_2 = _s1
        self.rd_ptr_sync = 0
        for k in range(WRITE_FIFO_ADDR_WIDTH + 1):
            self.rd_ptr_sync |= _xor_reduce_shift(_s2, k) << k
        if input_rst or _rst3_pre:
            self.rd_ptr_gray_sync_1 = 0
            self.rd_ptr_gray_sync_2 = 0
            self.rd_ptr_sync = 0

        self._n = None

    @property
    def input_rst_out(self):
        return self.rst_sync_3


class RawRd:
    """Cycle-accurate mirror of axi_vfifo_raw_rd (SEG_CNT=1, SEG_WIDTH=32,
    READ_FIFO_DEPTH=128, CTRL_OUT_EN=1)."""

    def __init__(self):
        self.reset()

    def reset(self):
        self.rst_sync_1 = 1
        self.rst_sync_2 = 1
        self.rst_sync_3 = 1
        self._rst_req_prev = 0
        self.araddr = 0
        self.arlen = 0
        self.arvalid = 0
        self.read_fifo_read_start_cnt = 0
        self.read_fifo_read_start_en = 0
        self.read_fifo_read_start_ptr = 0
        self.read_fifo_wr_ptr = 0
        self.read_fifo_wr_ptr_gray = 0
        # data seg
        self.seg_rd_ptr = 0
        self.seg_rd_ptr_gray = 0
        self.seg_mem = [0] * 128
        self.seg_rd_data = 0
        self.seg_rd_data_valid = 0
        # ctrl seg
        self.ctrl_rd_ptr = 0
        self.ctrl_rd_ptr_gray = 0
        self.ctrl_mem = [0] * 128
        self.ctrl_rd_data = 0
        self.ctrl_rd_data_valid = 0
        self.ctrl_output_ready = 0
        self.ctrl_output_data = 0
        self.ctrl_output_valid = 0
        self.temp_ctrl_output_data = 0
        self.temp_ctrl_output_valid = 0
        # sync regs
        self.rd_ptr_gray_sync_1 = 0
        self.rd_ptr_gray_sync_2 = 0
        self.rd_ptr_sync = 0
        self.wr_ptr_gray_sync_1 = 0
        self.wr_ptr_gray_sync_2 = 0
        self.ctrl_rd_ptr_gray_sync_1 = 0
        self.ctrl_rd_ptr_gray_sync_2 = 0
        self.ctrl_rd_ptr_sync = 0
        self.read_fifo_half_full = 0
        self.read_fifo_occupancy = 0
        self.read_fifo_occupancy_lookahead = 0
        # read engine
        self.rd_outstanding = 0
        self.rd_timeout_count = 0
        self.rd_timeout = 0
        self.rd_start_ptr = 0        # 17 bits
        self.rd_finish_ptr = 0       # 17 bits

    def comb(self, rvalid, rdata, arready, output_ready, output_ctrl_ready,
             wr_finish_ptr_in, cfg_base_addr, cfg_size_mask, cfg_enable,
             cfg_reset):
        # full/empty
        read_fifo_full = 1 if self.read_fifo_wr_ptr_gray == \
            ((self.rd_ptr_gray_sync_2 ^ 0x80) & 0xFF) else 0
        read_fifo_ctrl_full = 1 if self.read_fifo_wr_ptr_gray == \
            ((self.ctrl_rd_ptr_gray_sync_2 ^ 0x80) & 0xFF) else 0
        m_axi_rready = 1 if ((not read_fifo_full and
                              (not read_fifo_ctrl_full)) or cfg_reset) else 0

        # ---- read logic comb ----
        rd_start_ptr_next = self.rd_start_ptr
        rd_finish_ptr_next = self.rd_finish_ptr
        rd_outstanding_inc = 0
        rd_outstanding_dec = 0
        rd_outstanding_next = self.rd_outstanding
        rd_timeout_count_next = self.rd_timeout_count
        rd_timeout_next = self.rd_timeout

        araddr_next = self.araddr
        arlen_next = self.arlen
        arvalid_next = 1 if (self.arvalid and not arready) else 0

        # partial burst timeout handling
        rd_timeout_next = 1 if self.rd_timeout_count == 0 else 0
        if wr_finish_ptr_in == self.rd_start_ptr or self.arvalid:
            rd_timeout_count_next = 0xFF
            rd_timeout_next = 0
        elif self.rd_timeout_count > 0:
            rd_timeout_count_next = (self.rd_timeout_count - 1) & 0xFF

        # compute length based on DRAM occupancy
        avail = (wr_finish_ptr_in - self.rd_start_ptr) & 0x1FFFF
        if (avail >> READ_BURST_ADDR_WIDTH) != 0:
            rd_burst_len = READ_MAX_BURST_LEN_INT - \
                ((self.rd_start_ptr & READ_BURST_ADDR_MASK) >>
                 AXI_BURST_SIZE)
            rd_start_ptr = ((self.rd_start_ptr & ~READ_BURST_ADDR_MASK) +
                            (1 << READ_BURST_ADDR_WIDTH)) & 0x1FFFF
        else:
            rd_burst_len = (avail >> AXI_BURST_SIZE) & 0x1F
            rd_start_ptr = wr_finish_ptr_in

        self.read_fifo_read_start_cnt = rd_burst_len
        read_fifo_read_start_en = 0

        # generate AXI read bursts
        if not self.arvalid:
            araddr_next = (cfg_base_addr +
                           (self.rd_start_ptr & cfg_size_mask)) & 0xFFFF
            arlen_next = ((rd_burst_len - 1) & 0x1F) & 0xFF
            if cfg_enable and avail != 0 and \
                    self.read_fifo_occupancy_lookahead < \
                    2 ** READ_FIFO_ADDR_WIDTH - READ_MAX_BURST_LEN_INT:
                if (avail >> READ_BURST_ADDR_WIDTH) != 0 or self.rd_timeout:
                    read_fifo_read_start_en = 1
                    rd_outstanding_inc = rd_burst_len
                    arvalid_next = 1
                    rd_start_ptr_next = rd_start_ptr

        # handle AXI read completions
        if m_axi_rready and rvalid:
            rd_finish_ptr_next = \
                (self.rd_finish_ptr + AXI_BYTE_LANES_RAW) & 0x1FFFF
            rd_outstanding_dec = 1

        rd_outstanding_next = (self.rd_outstanding + rd_outstanding_inc -
                               rd_outstanding_dec) & 0xFF

        if cfg_reset:
            rd_start_ptr_next = 0
            rd_finish_ptr_next = 0

        self._n = {
            "m_axi_rready": m_axi_rready,
            "read_fifo_full": read_fifo_full,
            "read_fifo_read_start_en": read_fifo_read_start_en,
            "rd_outstanding_next": rd_outstanding_next,
            "rd_timeout_count_next": rd_timeout_count_next,
            "rd_timeout_next": rd_timeout_next,
            "araddr_next": araddr_next,
            "arlen_next": arlen_next,
            "arvalid_next": arvalid_next,
            "rd_start_ptr_next": rd_start_ptr_next,
            "rd_finish_ptr_next": rd_finish_ptr_next,
        }
        return {
            "m_axi_rready": m_axi_rready,
            "output_data": self.seg_rd_data,
            "output_valid": self.seg_rd_data_valid,
            "output_ctrl_data": self.ctrl_output_data,
            "output_ctrl_valid": self.ctrl_output_valid,
        }

    def edge(self, rvalid, rdata, output_ready, output_ctrl_ready,
             rst, cfg_reset, output_rst, cfg_reset_next=0):
        n = self._n
        # pre-edge gray captures
        _seg_rd_gray = self.seg_rd_ptr_gray
        _ctrl_rd_gray = self.ctrl_rd_ptr_gray
        _wr_gray = self.read_fifo_wr_ptr_gray
        # pre-edge rst_sync_3 (reset conditions sample it pre-edge)
        _rst3_pre = self.rst_sync_3
        # pre-edge ctrl rd data (skid transfer samples it pre-edge)
        _crd_pre = self.ctrl_rd_data

        # output_clk domain: async rst sync chain (R(t+1)=L(t)|L(t+1))
        _r1 = self.rst_sync_1
        _r2 = self.rst_sync_2
        self.rst_sync_1 = 1 if (cfg_reset or cfg_reset_next) else 0
        self.rst_sync_2 = _r1
        self.rst_sync_3 = _r2

        # clk domain: data/ctrl mem writes (pre-edge wr_ptr)
        _wrp = self.read_fifo_wr_ptr
        if not n["read_fifo_full"] and n["m_axi_rready"] and rvalid:
            self.seg_mem[_wrp & 0x7F] = rdata & 0xFFFFFFFF
            self.ctrl_mem[_wrp & 0x7F] = rdata & 0xFFFFFFFF
            nxt = (_wrp + 1) & 0xFF
            self.read_fifo_wr_ptr = nxt
            self.read_fifo_wr_ptr_gray = nxt ^ (nxt >> 1)

        # output_clk domain: per-seg read logic (data); pre-edge reads
        _sdv = self.seg_rd_data_valid
        self.seg_rd_data_valid = 1 if (_sdv and not output_ready) else 0
        if not self._seg_empty_data() and (not _sdv or output_ready):
            self.seg_rd_data = self.seg_mem[self.seg_rd_ptr & 0x7F]
            self.seg_rd_data_valid = 1
            nxt = (self.seg_rd_ptr + 1) & 0xFF
            self.seg_rd_ptr = nxt
            self.seg_rd_ptr_gray = nxt ^ (nxt >> 1)
        if output_rst or _rst3_pre:
            self.seg_rd_ptr = 0
            self.seg_rd_ptr_gray = 0
            self.seg_rd_data_valid = 0

        # output_clk domain: per-seg read logic (ctrl); pre-edge reads
        _cdv = self.ctrl_rd_data_valid
        self.ctrl_rd_data_valid = 1 if \
            (_cdv and not self.ctrl_output_ready) else 0
        if not self._seg_empty_ctrl() and \
                (not _cdv or self.ctrl_output_ready):
            self.ctrl_rd_data = self.ctrl_mem[self.ctrl_rd_ptr & 0x7F]
            self.ctrl_rd_data_valid = 1
            nxt = (self.ctrl_rd_ptr + 1) & 0xFF
            self.ctrl_rd_ptr = nxt
            self.ctrl_rd_ptr_gray = nxt ^ (nxt >> 1)
        if output_rst or _rst3_pre:
            self.ctrl_rd_ptr = 0
            self.ctrl_rd_ptr_gray = 0
            self.ctrl_rd_data_valid = 0

        # skid buffer (ctrl); the transfer uses the PRE-EDGE ready reg
        _ready_pre = self.ctrl_output_ready
        self.ctrl_output_ready = 1 if (output_ctrl_ready or
                                       (not self.temp_ctrl_output_valid and
                                        (not self.ctrl_output_valid or
                                         not _cdv))) else 0
        if _ready_pre:
            if output_ctrl_ready or not self.ctrl_output_valid:
                self.ctrl_output_data = _crd_pre
                self.ctrl_output_valid = _cdv
            else:
                self.temp_ctrl_output_data = _crd_pre
                self.temp_ctrl_output_valid = _cdv
        elif output_ctrl_ready:
            self.ctrl_output_data = self.temp_ctrl_output_data
            self.ctrl_output_valid = self.temp_ctrl_output_valid
            self.temp_ctrl_output_valid = 0
        if output_rst or _rst3_pre:
            self.ctrl_output_ready = 0
            self.ctrl_output_valid = 0
            self.temp_ctrl_output_valid = 0

        # clk domain: write logic (occupancy); pre-edge samples
        self.read_fifo_occupancy = \
            (_wrp - self.rd_ptr_sync) & 0xFF
        self.read_fifo_half_full = 1 if \
            ((_wrp - self.rd_ptr_sync) & 0xFF) >= \
            2 ** (READ_FIFO_ADDR_WIDTH - 1) else 0
        if n["read_fifo_read_start_en"]:
            self.read_fifo_read_start_ptr = \
                (self.read_fifo_read_start_ptr +
                 self.read_fifo_read_start_cnt) & 0xFF
            self.read_fifo_occupancy_lookahead = \
                (self.read_fifo_read_start_ptr +
                 self.read_fifo_read_start_cnt - self.rd_ptr_sync) & 0xFF
        else:
            self.read_fifo_occupancy_lookahead = \
                (self.read_fifo_read_start_ptr - self.rd_ptr_sync) & 0xFF
        if not n["read_fifo_full"] and n["m_axi_rready"] and rvalid:
            self.read_fifo_occupancy = ((_wrp + 1) - self.rd_ptr_sync) & 0xFF
        if rst or cfg_reset:
            self.read_fifo_read_start_ptr = 0
            self.read_fifo_wr_ptr = 0
            self.read_fifo_wr_ptr_gray = 0

        # clk domain: sync of rd ptr (output_clk -> clk); pre-edge samples
        _s1 = self.rd_ptr_gray_sync_1
        _s2 = self.rd_ptr_gray_sync_2
        self.rd_ptr_gray_sync_1 = _seg_rd_gray
        self.rd_ptr_gray_sync_2 = _s1
        self.rd_ptr_sync = 0
        for k in range(READ_FIFO_ADDR_WIDTH + 1):
            self.rd_ptr_sync |= _xor_reduce_shift(_s2, k) << k
        if rst or cfg_reset:
            self.rd_ptr_gray_sync_1 = 0
            self.rd_ptr_gray_sync_2 = 0
            self.rd_ptr_sync = 0

        # clk domain: sync of ctrl rd ptr; pre-edge samples
        _s1 = self.ctrl_rd_ptr_gray_sync_1
        _s2 = self.ctrl_rd_ptr_gray_sync_2
        self.ctrl_rd_ptr_gray_sync_1 = _ctrl_rd_gray
        self.ctrl_rd_ptr_gray_sync_2 = _s1
        self.ctrl_rd_ptr_sync = 0
        for k in range(READ_FIFO_ADDR_WIDTH + 1):
            self.ctrl_rd_ptr_sync |= _xor_reduce_shift(_s2, k) << k
        if rst or cfg_reset:
            self.ctrl_rd_ptr_gray_sync_1 = 0
            self.ctrl_rd_ptr_gray_sync_2 = 0
            self.ctrl_rd_ptr_sync = 0

        # output_clk domain: sync of wr ptr (clk -> output_clk)
        _s1 = self.wr_ptr_gray_sync_1
        self.wr_ptr_gray_sync_1 = _wr_gray
        self.wr_ptr_gray_sync_2 = _s1
        if output_rst or _rst3_pre:
            self.wr_ptr_gray_sync_1 = 0
            self.wr_ptr_gray_sync_2 = 0

        # clk domain: read engine regs
        self.rd_outstanding = n["rd_outstanding_next"]
        self.rd_timeout_count = n["rd_timeout_count_next"]
        self.rd_timeout = n["rd_timeout_next"]
        self.araddr = n["araddr_next"]
        self.arlen = n["arlen_next"]
        self.arvalid = n["arvalid_next"]
        self.rd_start_ptr = n["rd_start_ptr_next"]
        self.rd_finish_ptr = n["rd_finish_ptr_next"]
        if rst:
            self.rd_outstanding = 0
            self.arvalid = 0

        self._n = None

    def _seg_empty_data(self):
        return 1 if self.seg_rd_ptr_gray == self.wr_ptr_gray_sync_2 else 0

    def _seg_empty_ctrl(self):
        return 1 if self.ctrl_rd_ptr_gray == self.wr_ptr_gray_sync_2 else 0

    @property
    def output_rst_out(self):
        return self.rst_sync_3

    @property
    def read_active(self):
        return 1 if self.rd_outstanding != 0 else 0


class Dec:
    """Cycle-accurate mirror of axi_vfifo_dec (SEG_CNT=2, SEG_WIDTH=32,
    AXIS_DATA_WIDTH=32)."""

    def __init__(self):
        self.reset()

    def reset(self):
        self.frame = 0
        self.last = 0
        self.extra_cycle = 0
        self.last_straddle = 0
        self.seg_cnt = 0               # 10 bits
        self.hdr_parity_err = 0
        self.out_frame = 0
        self.out_seg_offset = 0        # 1 bit
        self.output_offset = 0         # 1 bit
        self.out_seg_consumed = 0      # 2 bits
        self.out_seg_consumed_reg = 0
        # ctrl fifo (2 segs)
        self.ctrl_wr_ptr = [0, 0]
        self.ctrl_rd_ptr = [0, 0]
        self.ctrl_mem_sop = [[0] * 32, [0] * 32]
        self.ctrl_mem_eop = [[0] * 32, [0] * 32]
        self.ctrl_mem_end = [[0] * 32, [0] * 32]
        self.ctrl_mem_last = [[0] * 32, [0] * 32]
        self.ctrl_mem_last_len = [[0] * 32, [0] * 32]
        self.ctrl_rd_sop = [0, 0]
        self.ctrl_rd_eop = [0, 0]
        self.ctrl_rd_end = [0, 0]
        self.ctrl_rd_last = [0, 0]
        self.ctrl_rd_last_len = [0, 0]
        self.ctrl_rd_valid = [0, 0]
        self.ctrl_half_full = [0, 0]
        # input data regs (EXPAND_INPUT=0 -> unused)
        self.input_data_int = 0
        self.input_valid_int = [0, 0]
        # out ctrl
        self.out_ctrl_en = 0
        self.out_ctrl_hdr = 0
        self.out_ctrl_last = 0
        self.out_ctrl_last_len = 0     # 2 bits
        self.out_ctrl_seg_offset = 0   # 1 bit
        # meta regs
        self.axis_tid = 0
        self.axis_tdest = 0
        self.axis_tuser = 0
        # output fifo
        self.out_fifo_wr_ptr = 0
        self.out_fifo_rd_ptr = 0
        self.out_fifo_half_full = 0
        self.out_fifo_tdata = [0] * 32
        self.out_fifo_tkeep = [0] * 32
        self.out_fifo_tlast = [0] * 32
        self.out_fifo_tid = [0] * 32
        self.out_fifo_tdest = [0] * 32
        self.out_fifo_tuser = [0] * 32
        # m_axis output regs
        self.m_axis_tdata = 0
        self.m_axis_tkeep = 0
        self.m_axis_tvalid = 0
        self.m_axis_tlast = 0
        self.m_axis_tid = 0
        self.m_axis_tdest = 0
        self.m_axis_tuser = 0

    @property
    def ctrl_fifo_half_full(self):
        return 1 if (self.ctrl_half_full[0] or self.ctrl_half_full[1]) else 0

    def comb(self, input_data, input_valid, input_ctrl_data, input_ctrl_valid,
             m_axis_tready):
        # ---- parse segment headers ----
        input_ctrl_ready_cmb = 0
        frame_next = self.frame
        frame_cyc = self.frame
        last_next = self.last
        last_cyc = self.last
        extra_cycle_next = self.extra_cycle
        extra_cycle_cyc = self.extra_cycle
        last_straddle_next = self.last_straddle
        last_straddle_cyc = self.last_straddle
        seg_cnt_next = self.seg_cnt
        seg_cnt_cyc = self.seg_cnt
        hdr_parity_err_next = 0
        hdr_parity_err_cyc = 0

        ctrl_fifo_wr_sop = [0, 0]
        ctrl_fifo_wr_eop = [0, 0]
        ctrl_fifo_wr_end = [0, 0]
        ctrl_fifo_wr_last = [0, 0]
        ctrl_fifo_wr_last_len = [0, 0]
        ctrl_fifo_wr_en = [0, 0]

        seg_valid = [input_ctrl_valid[0], input_ctrl_valid[1]]
        seg_hdr_start_pkt = [(input_ctrl_data >> (32 * s)) & 1 for s in
                             range(SEG_CNT)]
        seg_hdr_last = [(input_ctrl_data >> (32 * s + 1)) & 1 for s in
                        range(SEG_CNT)]
        seg_hdr_len = [(input_ctrl_data >> (32 * s + 4)) & 0xFFF for s in
                       range(SEG_CNT)]
        seg_hdr_seg_cnt = [((seg_hdr_len[s] + SEG_BYTE_LANES) >>
                            SEG_BYTE_IDX_WIDTH) & 0x3FF for s in range(SEG_CNT)]
        seg_hdr_last_straddle = [1 if (((seg_hdr_len[s] &
                                         (SEG_BYTE_LANES - 1)) + HDR_SIZE) >>
                                       SEG_BYTE_IDX_WIDTH) != 0 else 0
                                 for s in range(SEG_CNT)]
        seg_hdr_parity_err = []
        for s in range(SEG_CNT):
            w = (input_ctrl_data >> (32 * s)) & 0xFFFFFFFF
            p1 = 0
            for k in range(3):
                p1 ^= (w >> k) & 1
            p2 = 0
            for k in range(3, 16):
                p2 ^= (w >> k) & 1
            seg_hdr_parity_err.append(p1 ^ p2)

        # seg_valid_straddle = {2{seg_valid}} >> 1
        seg_valid_straddle = ((seg_valid[0] | (seg_valid[1] << 1) |
                               (seg_valid[0] << 2) |
                               (seg_valid[1] << 3)) >> 1) & 0x3

        for seg in range(SEG_CNT):
            if not frame_cyc:
                if seg_valid[seg]:
                    if seg_hdr_start_pkt[seg]:
                        # start of frame
                        last_cyc = seg_hdr_last[seg]
                        extra_cycle_cyc = 0
                        last_straddle_cyc = seg_hdr_last_straddle[seg]
                        seg_cnt_cyc = seg_hdr_seg_cnt[seg]
                        ctrl_fifo_wr_sop[seg] = 1
                        ctrl_fifo_wr_last_len[seg] = seg_hdr_len[seg] & 0x3
                        frame_cyc = 1
                    # else: consume null segment
                    if seg_hdr_parity_err[seg]:
                        hdr_parity_err_cyc = 1
            if frame_cyc:
                if extra_cycle_cyc:
                    # extra cycle
                    frame_cyc = 0
                    extra_cycle_cyc = 0
                    ctrl_fifo_wr_eop[seg] = 1
                elif seg_cnt_cyc == 1:
                    # last output cycle
                    if last_cyc:
                        ctrl_fifo_wr_last[seg] = 1
                    if last_straddle_cyc:
                        # last output cycle, with segment straddle
                        extra_cycle_cyc = 1
                        ctrl_fifo_wr_end[seg] = 1
                    else:
                        # last output cycle, no segment straddle
                        frame_cyc = 0
                        ctrl_fifo_wr_eop[seg] = 1
                        ctrl_fifo_wr_end[seg] = 1
                # else: middle cycle
            seg_cnt_cyc = (seg_cnt_cyc - 1) & 0x3FF

        if (seg_valid[0] and seg_valid[1]) and not self.ctrl_fifo_half_full:
            input_ctrl_ready_cmb = 0x3
            ctrl_fifo_wr_en = [1, 1]
            frame_next = frame_cyc
            last_next = last_cyc
            extra_cycle_next = extra_cycle_cyc
            last_straddle_next = last_straddle_cyc
            seg_cnt_next = seg_cnt_cyc
            hdr_parity_err_next = hdr_parity_err_cyc

        # ---- re-pack data ----
        input_ready_cmb = self.out_seg_consumed_reg

        out_frame_next = self.out_frame
        out_frame_cyc = self.out_frame
        out_seg_offset_next = self.out_seg_offset
        out_seg_offset_cyc = self.out_seg_offset
        output_offset_next = self.output_offset
        output_offset_cyc = 0
        out_seg_consumed_next = 0

        out_ctrl_en_next = 0
        out_ctrl_hdr_next = 0
        out_ctrl_last_next = 0
        out_ctrl_last_len_next = self.out_ctrl_last_len
        out_ctrl_seg_offset_next = self.out_ctrl_seg_offset

        axis_tid_next = self.axis_tid
        axis_tdest_next = self.axis_tdest
        axis_tuser_next = self.axis_tuser

        ctrl_fifo_rd_en = 0

        rd_valid = self.ctrl_rd_valid[0] | (self.ctrl_rd_valid[1] << 1)
        rd_sop = self.ctrl_rd_sop[0] | (self.ctrl_rd_sop[1] << 1)
        rd_eop = self.ctrl_rd_eop[0] | (self.ctrl_rd_eop[1] << 1)
        rd_end = self.ctrl_rd_end[0] | (self.ctrl_rd_end[1] << 1)
        rd_last = self.ctrl_rd_last[0] | (self.ctrl_rd_last[1] << 1)

        # apply segment offset ({2{ctrl_fifo_rd_valid}} >> out_seg_offset_reg)
        off = self.out_seg_offset
        shift_out_seg_valid = ((rd_valid | (rd_valid << 2)) >> off) & 0x3
        shift_out_seg_valid_straddle = ((rd_valid | (rd_valid << 2)) >>
                                        (off + 1)) & 0x3
        shift_out_seg_valid_straddle &= ~(1 << (SEG_CNT - 1))
        shift_out_seg_sop = ((rd_sop | (rd_sop << 2)) >> off) & 0x3
        shift_out_seg_eop = ((rd_eop | (rd_eop << 2)) >> off) & 0x3
        shift_out_seg_end = ((rd_end | (rd_end << 2)) >> off) & 0x3
        shift_out_seg_last = ((rd_last | (rd_last << 2)) >> off) & 0x3

        out_valid = 0
        out_valid_straddle = 0
        out_frame = out_frame_cyc
        out_abort = 0
        out_done = 0
        out_seg_consumed = 0

        out_ctrl_seg_offset_next = out_seg_offset_reg = self.out_seg_offset
        out_cur_seg = self.out_seg_offset
        for out_seg in range(SEG_CNT):
            # 1-bit temp: +1 toggles (like the RTL's declared width)
            out_seg_offset_cyc = (out_seg_offset_cyc + 1) & 0x1
            # check for contiguous valid segments
            mask = 0x3 >> (SEG_CNT - 1 - out_seg)
            out_valid = 1 if ((~shift_out_seg_valid) & mask & 0x3) == 0 \
                else 0
            out_valid_straddle = shift_out_seg_valid_straddle & 1

            if not out_frame_cyc:
                if out_valid:
                    if shift_out_seg_sop & 1:
                        # start of frame
                        out_frame_cyc = 1
                        if not out_done:
                            out_ctrl_hdr_next = 1
                            out_ctrl_last_len_next = \
                                self.ctrl_rd_last_len[out_cur_seg] & 0x3
                            out_ctrl_seg_offset_next = out_cur_seg
                    elif not out_abort:
                        # consume null segment
                        out_seg_consumed |= 1 << out_cur_seg
                        out_seg_consumed_next = out_seg_consumed
                        ctrl_fifo_rd_en = out_seg_consumed
                        out_seg_offset_next = out_seg_offset_cyc
            out_frame = out_frame_cyc

            if out_frame and not out_done:
                if shift_out_seg_end & 1:
                    # last output cycle
                    out_frame_cyc = 0
                    out_done = 1
                    if shift_out_seg_last & 1:
                        out_ctrl_last_next = 1
                    if out_valid and (out_valid_straddle or
                                      (shift_out_seg_eop & 1)) and \
                            self._tready_int():
                        out_ctrl_en_next = 1
                        out_seg_consumed |= 1 << out_cur_seg
                        out_seg_consumed_next = out_seg_consumed
                        ctrl_fifo_rd_en = out_seg_consumed
                        out_frame_next = out_frame_cyc
                        out_seg_offset_next = out_seg_offset_cyc
                    else:
                        out_abort = 1
                elif output_offset_cyc == AXIS_SEG_CNT - 1:
                    # output full
                    out_done = 1
                    if out_valid and out_valid_straddle and \
                            self._tready_int():
                        out_ctrl_en_next = 1
                        out_seg_consumed |= 1 << out_cur_seg
                        out_seg_consumed_next = out_seg_consumed
                        ctrl_fifo_rd_en = out_seg_consumed
                        out_frame_next = out_frame_cyc
                        out_seg_offset_next = out_seg_offset_cyc
                    else:
                        out_abort = 1
                else:
                    # middle cycle
                    if out_valid and out_valid_straddle and \
                            self._tready_int():
                        out_seg_consumed |= 1 << out_cur_seg
                    else:
                        out_abort = 1

                if output_offset_cyc == AXIS_SEG_CNT - 1:
                    output_offset_cyc = 0
                else:
                    output_offset_cyc = (output_offset_cyc + 1) & 0x3

            out_cur_seg = (out_cur_seg + 1) & 0x1

            shift_out_seg_valid_straddle >>= 1
            shift_out_seg_sop >>= 1
            shift_out_seg_eop >>= 1
            shift_out_seg_end >>= 1
            shift_out_seg_last >>= 1

        # construct output
        input_ready_cmb = out_seg_consumed_reg = self.out_seg_consumed_reg

        # input_data_full = {2{input_data}} (128 bits)
        vfull = (input_data & 0xFFFFFFFFFFFFFFFF) | \
            ((input_data & 0xFFFFFFFFFFFFFFFF) << 64)
        m_axis_tdata_int = (vfull >> (SEG_WIDTH * self.out_ctrl_seg_offset +
                                      HDR_WIDTH)) & 0xFFFFFFFF
        if self.out_ctrl_last:
            m_axis_tkeep_int = (0xF >> (4 - 1 - self.out_ctrl_last_len)) & 0xF
        else:
            m_axis_tkeep_int = 0xF
        m_axis_tlast_int = self.out_ctrl_last

        if self.out_ctrl_hdr:
            axis_tid_next = (vfull >> (SEG_WIDTH * self.out_ctrl_seg_offset +
                                       16 + 0)) & 0xFF
            axis_tdest_next = (vfull >> (SEG_WIDTH * self.out_ctrl_seg_offset +
                                         16 + 0)) & 0xFF
            axis_tuser_next = (vfull >> (SEG_WIDTH * self.out_ctrl_seg_offset +
                                         16 + 0)) & 0x1

        m_axis_tvalid_int = self.out_ctrl_en
        m_axis_tid_int = axis_tid_next
        m_axis_tdest_int = axis_tdest_next
        m_axis_tuser_int = axis_tuser_next

        self._n = {
            "input_ctrl_ready": input_ctrl_ready_cmb,
            "input_ready": input_ready_cmb,
            "frame": frame_next, "last": last_next,
            "extra_cycle": extra_cycle_next,
            "last_straddle": last_straddle_next,
            "seg_cnt": seg_cnt_next,
            "hdr_parity_err": hdr_parity_err_next,
            "ctrl_fifo_wr_sop": ctrl_fifo_wr_sop,
            "ctrl_fifo_wr_eop": ctrl_fifo_wr_eop,
            "ctrl_fifo_wr_end": ctrl_fifo_wr_end,
            "ctrl_fifo_wr_last": ctrl_fifo_wr_last,
            "ctrl_fifo_wr_last_len": ctrl_fifo_wr_last_len,
            "ctrl_fifo_wr_en": ctrl_fifo_wr_en,
            "ctrl_fifo_rd_en": ctrl_fifo_rd_en,
            "out_frame": out_frame_next,
            "out_seg_offset": out_seg_offset_next,
            "output_offset": output_offset_next,
            "out_seg_consumed_reg": out_seg_consumed_next,
            "out_ctrl_en": out_ctrl_en_next,
            "out_ctrl_hdr": out_ctrl_hdr_next,
            "out_ctrl_last": out_ctrl_last_next,
            "out_ctrl_last_len": out_ctrl_last_len_next,
            "out_ctrl_seg_offset": out_ctrl_seg_offset_next,
            "axis_tid": axis_tid_next,
            "axis_tdest": axis_tdest_next,
            "axis_tuser": axis_tuser_next,
            "m_axis_tdata_int": m_axis_tdata_int,
            "m_axis_tkeep_int": m_axis_tkeep_int,
            "m_axis_tlast_int": m_axis_tlast_int,
            "m_axis_tvalid_int": m_axis_tvalid_int,
            "m_axis_tid_int": m_axis_tid_int,
            "m_axis_tdest_int": m_axis_tdest_int,
            "m_axis_tuser_int": m_axis_tuser_int,
        }
        return {
            "input_ready": input_ready_cmb,
            "input_ctrl_ready": input_ctrl_ready_cmb,
            "m_axis_tdata": self.m_axis_tdata,
            "m_axis_tkeep": self.m_axis_tkeep,
            "m_axis_tvalid": self.m_axis_tvalid,
            "m_axis_tlast": self.m_axis_tlast,
            "m_axis_tid": self.m_axis_tid,
            "m_axis_tdest": self.m_axis_tdest,
            "m_axis_tuser": self.m_axis_tuser,
        }

    def _tready_int(self):
        return 1 if not self.out_fifo_half_full else 0

    def edge(self, rst, fifo_rst_in, m_axis_tready):
        n = self._n

        # ctrl fifo per-seg edge (pre-edge samples)
        for seg in range(SEG_CNT):
            _rdv = self.ctrl_rd_valid[seg]
            _wrp = self.ctrl_wr_ptr[seg]
            _rdp = self.ctrl_rd_ptr[seg]
            self.ctrl_rd_valid[seg] = 1 if \
                (_rdv and not ((n["ctrl_fifo_rd_en"] >> seg) & 1)) else 0
            self.ctrl_half_full[seg] = 1 if \
                ((_wrp - _rdp) & 0x3F) >= \
                2 ** (CTRL_FIFO_ADDR_WIDTH - 1) else 0
            if n["ctrl_fifo_wr_en"][seg]:
                a = _wrp & 0x1F
                self.ctrl_mem_sop[seg][a] = n["ctrl_fifo_wr_sop"][seg]
                self.ctrl_mem_eop[seg][a] = n["ctrl_fifo_wr_eop"][seg]
                self.ctrl_mem_end[seg][a] = n["ctrl_fifo_wr_end"][seg]
                self.ctrl_mem_last[seg][a] = n["ctrl_fifo_wr_last"][seg]
                self.ctrl_mem_last_len[seg][a] = \
                    n["ctrl_fifo_wr_last_len"][seg]
                self.ctrl_wr_ptr[seg] = (_wrp + 1) & 0x3F
            empty = 1 if _wrp == _rdp else 0
            if not empty and (not _rdv or
                              ((n["ctrl_fifo_rd_en"] >> seg) & 1)):
                a = _rdp & 0x1F
                self.ctrl_rd_sop[seg] = self.ctrl_mem_sop[seg][a]
                self.ctrl_rd_eop[seg] = self.ctrl_mem_eop[seg][a]
                self.ctrl_rd_end[seg] = self.ctrl_mem_end[seg][a]
                self.ctrl_rd_last[seg] = self.ctrl_mem_last[seg][a]
                self.ctrl_rd_last_len[seg] = self.ctrl_mem_last_len[seg][a]
                self.ctrl_rd_valid[seg] = 1
                self.ctrl_rd_ptr[seg] = (_rdp + 1) & 0x3F
            if rst or fifo_rst_in:
                self.ctrl_wr_ptr[seg] = 0
                self.ctrl_rd_ptr[seg] = 0
                self.ctrl_rd_valid[seg] = 0

        # main regs
        self.frame = n["frame"]
        self.last = n["last"]
        self.extra_cycle = n["extra_cycle"]
        self.last_straddle = n["last_straddle"]
        self.seg_cnt = n["seg_cnt"]
        self.hdr_parity_err = n["hdr_parity_err"]
        self.out_frame = n["out_frame"]
        # 1-bit regs: the RTL truncates the assigned values here
        self.out_seg_offset = n["out_seg_offset"] & 1
        self.output_offset = n["output_offset"] & 1
        self.out_seg_consumed_reg = n["out_seg_consumed_reg"]
        self.out_ctrl_en = n["out_ctrl_en"]
        self.out_ctrl_hdr = n["out_ctrl_hdr"]
        self.out_ctrl_last = n["out_ctrl_last"]
        self.out_ctrl_last_len = n["out_ctrl_last_len"]
        self.out_ctrl_seg_offset = n["out_ctrl_seg_offset"] & 1
        self.axis_tid = n["axis_tid"]
        self.axis_tdest = n["axis_tdest"]
        self.axis_tuser = n["axis_tuser"]

        # output datapath (out fifo + output reg); pre-edge samples
        _tv = self.m_axis_tvalid
        _wrp = self.out_fifo_wr_ptr
        _rdp = self.out_fifo_rd_ptr
        empty = 1 if _wrp == _rdp else 0
        self.m_axis_tvalid = 1 if (_tv and not m_axis_tready) else 0
        self.out_fifo_half_full = 1 if \
            ((_wrp - _rdp) & 0x3F) >= \
            2 ** (OUTPUT_FIFO_ADDR_WIDTH - 1) else 0
        full = 1 if _wrp == ((_rdp ^ 0x20) & 0x3F) else 0
        if not full and n["m_axis_tvalid_int"]:
            a = _wrp & 0x1F
            self.out_fifo_tdata[a] = n["m_axis_tdata_int"]
            self.out_fifo_tkeep[a] = n["m_axis_tkeep_int"]
            self.out_fifo_tlast[a] = n["m_axis_tlast_int"]
            self.out_fifo_tid[a] = n["m_axis_tid_int"]
            self.out_fifo_tdest[a] = n["m_axis_tdest_int"]
            self.out_fifo_tuser[a] = n["m_axis_tuser_int"]
            self.out_fifo_wr_ptr = (_wrp + 1) & 0x3F
        if not empty and (not _tv or m_axis_tready):
            a = _rdp & 0x1F
            self.m_axis_tdata = self.out_fifo_tdata[a]
            self.m_axis_tkeep = self.out_fifo_tkeep[a]
            self.m_axis_tvalid = 1
            self.m_axis_tlast = self.out_fifo_tlast[a]
            self.m_axis_tid = self.out_fifo_tid[a]
            self.m_axis_tdest = self.out_fifo_tdest[a]
            self.m_axis_tuser = self.out_fifo_tuser[a]
            self.out_fifo_rd_ptr = (_rdp + 1) & 0x3F
        if rst or fifo_rst_in:
            self.out_fifo_wr_ptr = 0
            self.out_fifo_rd_ptr = 0
            self.m_axis_tvalid = 0

        if rst or fifo_rst_in:
            self.frame = 0
            self.hdr_parity_err = 0
            self.out_frame = 0
            self.out_seg_offset = 0
            self.output_offset = 0
            self.out_seg_consumed_reg = 0
            self.out_ctrl_en = 0

        self._n = None


class Raw:
    """Mirror of one axi_vfifo_raw instance (fifo reset/enable regs)."""

    def __init__(self):
        self.fifo_reset_reg = 1
        self.fifo_enable_reg = 0
        self.fifo_base_addr_reg = 0
        self.fifo_size_mask_reg = 0
        self.rst_sync_1 = 1
        self.rst_sync_2 = 1
        self.rst_sync_3 = 1
        self._rst_req_prev = 0
        self._rst_req_int = 0

    def comb(self, rst, input_rst, output_rst, cfg_reset, cfg_base_addr,
             cfg_size_mask, cfg_enable, sts_write_active, sts_read_active,
             rst_req_in):
        rst_req_out = 1 if (rst or input_rst or output_rst or cfg_reset) \
            else 0
        rst_req_int = 1 if (rst_req_in or rst_req_out) else 0
        fifo_reset_next = 0
        fifo_enable_next = self.fifo_enable_reg
        fifo_base_addr_next = self.fifo_base_addr_reg
        fifo_size_mask_next = self.fifo_size_mask_reg
        if cfg_reset or self.rst_sync_3:
            fifo_reset_next = 1
        if self.fifo_reset_reg:
            fifo_enable_next = 0
            # hold reset until everything is flushed
            if sts_write_active or sts_read_active:
                fifo_reset_next = 1
        elif not self.fifo_enable_reg and cfg_enable:
            fifo_base_addr_next = cfg_base_addr & ADDR_MASK
            fifo_size_mask_next = (cfg_size_mask | ((~ADDR_MASK) & 0xFFFF)) \
                & 0xFFFF
            fifo_enable_next = 1
        self._rst_req_int = rst_req_int
        self._rst_req_out = rst_req_out
        self._fifo_reset_next = fifo_reset_next
        self._fifo_enable_next = fifo_enable_next
        self._fifo_base_addr_next = fifo_base_addr_next
        self._fifo_size_mask_next = fifo_size_mask_next
        return rst_req_out

    def edge(self, rst, cfg_reset_next=0, rst_req_in_next=0):
        _r1 = self.rst_sync_1
        _r2 = self.rst_sync_2
        # async-set semantics: the reg asserts on the level rise and holds
        # one extra cycle: R(t+1) = L(t) | L(t+1)
        l_cur = 1 if self._rst_req_int else 0
        l_next = 1 if (rst or rst or rst or cfg_reset_next or
                       rst_req_in_next) else 0
        self.rst_sync_1 = 1 if (l_cur or l_next) else 0
        self.rst_sync_2 = _r1
        self.rst_sync_3 = _r2

        self.fifo_reset_reg = self._fifo_reset_next
        self.fifo_enable_reg = self._fifo_enable_next
        self.fifo_base_addr_reg = self._fifo_base_addr_next
        self.fifo_size_mask_reg = self._fifo_size_mask_next
        if rst:
            self.fifo_reset_reg = 1
            self.fifo_enable_reg = 0


class Vfifo:
    """Mirror of the upstream axi_vfifo top module (AXI_CH=2)."""

    def __init__(self):
        self.reset()

    def reset(self):
        self.cfg_fifo_base_addr_reg = 0
        self.cfg_fifo_size_mask_reg = 0
        self.cfg_enable_reg = 0
        self.cfg_reset_reg = 0
        # status sync (m_axis_clk domain)
        self.sts_hdr_parity_err_cnt = 0
        self.sts_hdr_parity_err_reg = 0
        # status sync (clk domain)
        self.sts_sync_count = 0
        self.sts_sync_flag = 0
        self.sts_fifo_occupancy_sync = 0
        self.sts_fifo_empty_sync_1 = 0
        self.sts_fifo_empty_sync_2 = 0
        self.sts_fifo_full_sync_1 = 0
        self.sts_fifo_full_sync_2 = 0
        self.sts_reset_sync_1 = 0
        self.sts_reset_sync_2 = 0
        self.sts_active_sync_1 = 0
        self.sts_active_sync_2 = 0
        self.sts_hdr_parity_err_sync_1 = 0
        self.sts_hdr_parity_err_sync_2 = 0
        # per channel
        self.ch = []
        for _ in range(AXI_CH):
            self.ch.append({
                "cfg_enable_sync_1": 0,
                "cfg_enable_sync_2": 0,
                "cfg_reset_sync_1": 0,
                "cfg_reset_sync_2": 0,
                "sts_occupancy_reg": 0,
                "sts_flag_sync_1": 0,
                "sts_flag_sync_2": 0,
                "sts_flag_sync_3": 0,
            })
        self.enc = Enc()
        self.raw_wr = [RawWr() for _ in range(AXI_CH)]
        self.raw_rd = [RawRd() for _ in range(AXI_CH)]
        self.raw = [Raw() for _ in range(AXI_CH)]
        self.dec = Dec()

    def comb(self, s_tvalid, s_tdata, s_tkeep, s_tlast, m_axis_tready,
             awready, arready, wready, bvalid, rvalid, rdata, rst):
        # ---- top-level wires ----
        s_axis_rst_out = 1 if any(
            w.input_rst_out for w in self.raw_wr) else 0
        m_axis_rst_out = 1 if any(
            r.output_rst_out for r in self.raw_rd) else 0

        # encoder (fifo_watermark_in = |ch_input_watermark)
        watermark = 0
        for ch in range(AXI_CH):
            w = self.raw_wr[ch]
            seg_full = 1 if w.seg_wr_ptr_gray == \
                ((w.rd_ptr_gray_sync_2 ^ 0x60) & 0x7F) else 0
            if (w.seg_occupancy > WATERMARK_LEVEL) or w.rst_sync_3:
                watermark = 1
        enc_out = self.enc.comb(s_tvalid, s_tdata, s_tkeep, s_tlast, 0,
                                s_axis_rst_out, watermark)
        # the raw modules sample the encoder's REGISTER outputs (pre-edge)
        ch_input_data = self.enc.output_data
        ch_input_valid = self.enc.output_valid

        # per channel raw_wr comb (cfg comes from the raw MODULE's own regs,
        # exactly like the RTL's .cfg_reset(fifo_reset_reg) wiring)
        raw_wr_out = []
        for ch in range(AXI_CH):
            c = self.ch[ch]
            rw = self.raw_wr[ch]
            rmod = self.raw[ch]
            wout = rw.comb(
                input_valid=ch_input_valid[ch],
                input_data=(ch_input_data >> (32 * ch)) & 0xFFFFFFFF,
                awready=awready[ch], wready=wready[ch],
                bvalid=bvalid[ch],
                cfg_base_addr=rmod.fifo_base_addr_reg,
                cfg_size_mask=rmod.fifo_size_mask_reg,
                cfg_enable=rmod.fifo_enable_reg,
                cfg_reset=rmod.fifo_reset_reg,
                input_rst=rst,
                rd_finish_ptr_in=self.raw_rd[ch].rd_finish_ptr)
            raw_wr_out.append(wout)

        # per channel raw_rd comb (ready values come from the dec, computed
        # after this; the comb itself only needs pre-edge regs)
        raw_rd_out = []
        for ch in range(AXI_CH):
            c = self.ch[ch]
            rr = self.raw_rd[ch]
            rmod = self.raw[ch]
            rout = rr.comb(
                rvalid=rvalid[ch], rdata=rdata[ch],
                arready=arready[ch],
                output_ready=0, output_ctrl_ready=0,
                wr_finish_ptr_in=self.raw_wr[ch].wr_finish_ptr,
                cfg_base_addr=rmod.fifo_base_addr_reg,
                cfg_size_mask=rmod.fifo_size_mask_reg,
                cfg_enable=rmod.fifo_enable_reg,
                cfg_reset=rmod.fifo_reset_reg)
            raw_rd_out.append(rout)

        # decoder comb
        input_data = (raw_rd_out[0]["output_data"] |
                      (raw_rd_out[1]["output_data"] << 32))
        input_valid = [raw_rd_out[0]["output_valid"],
                       raw_rd_out[1]["output_valid"]]
        input_ctrl_data = (raw_rd_out[0]["output_ctrl_data"] |
                           (raw_rd_out[1]["output_ctrl_data"] << 32))
        input_ctrl_valid = [raw_rd_out[0]["output_ctrl_valid"],
                            raw_rd_out[1]["output_ctrl_valid"]]
        dec_out = self.dec.comb(input_data, input_valid, input_ctrl_data,
                                input_ctrl_valid, m_axis_tready)

        # raw module comb (rst_req chain + fifo enable/reset regs)
        # NOTE: input_rst/output_rst are the EXTERNAL resets (s_axis_rst /
        # m_axis_rst = the wrapper rst), not the sync-chain outputs.
        rst_req_any = 0
        for ch in range(AXI_CH):
            c = self.ch[ch]
            out_ch = self.raw[ch].comb(
                rst, rst, rst,
                c["cfg_reset_sync_2"],
                (self.cfg_fifo_base_addr_reg >> (16 * ch)) & 0xFFFF,
                self.cfg_fifo_size_mask_reg,
                c["cfg_enable_sync_2"],
                raw_wr_out[ch]["sts_write_active"],
                self.raw_rd[ch].read_active,
                0)
            rst_req_any |= out_ch
        for ch in range(AXI_CH):
            c = self.ch[ch]
            self.raw[ch].comb(
                rst, rst, rst,
                c["cfg_reset_sync_2"],
                (self.cfg_fifo_base_addr_reg >> (16 * ch)) & 0xFFFF,
                self.cfg_fifo_size_mask_reg,
                c["cfg_enable_sync_2"],
                raw_wr_out[ch]["sts_write_active"],
                self.raw_rd[ch].read_active,
                rst_req_any)

        self._comb = {
            "s_axis_rst_out": s_axis_rst_out,
            "m_axis_rst_out": m_axis_rst_out,
            "s_axis_tready": enc_out["tready"],
            "ch_input_valid": ch_input_valid,
            "ch_input_data": ch_input_data,
            "raw_wr_out": raw_wr_out,
            "raw_rd_out": raw_rd_out,
            "dec_out": dec_out,
            "dec_hdr_parity_err": self.dec.hdr_parity_err,
        }
        return {
            "s_axis_tready": enc_out["tready"],
            "m_axis_tdata": dec_out["m_axis_tdata"],
            "m_axis_tkeep": dec_out["m_axis_tkeep"],
            "m_axis_tvalid": dec_out["m_axis_tvalid"],
            "m_axis_tlast": dec_out["m_axis_tlast"],
            "m_axi_awvalid": [raw_wr_out[0]["awvalid"],
                              raw_wr_out[1]["awvalid"]],
            "m_axi_wvalid": [raw_wr_out[0]["wvalid"],
                             raw_wr_out[1]["wvalid"]],
            "m_axi_wlast": [raw_wr_out[0]["wlast"],
                            raw_wr_out[1]["wlast"]],
            "m_axi_bready": [raw_wr_out[0]["bready"],
                             raw_wr_out[1]["bready"]],
            "m_axi_arvalid": [self.raw_rd[0].arvalid,
                              self.raw_rd[1].arvalid],
            "m_axi_rready": [raw_rd_out[0]["m_axi_rready"],
                             raw_rd_out[1]["m_axi_rready"]],
            "sts_fifo_occupancy": self.sts_fifo_occupancy_sync,
            "sts_fifo_empty": self.sts_fifo_empty_sync_2,
            "sts_fifo_full": self.sts_fifo_full_sync_2,
            "sts_reset": self.sts_reset_sync_2,
            "sts_active": self.sts_active_sync_2,
            "sts_hdr_parity_err": self.sts_hdr_parity_err_sync_2,
        }

    def edge(self, cfg_base_addr, cfg_size_mask, cfg_enable, cfg_reset,
             rst, awready, arready, wready, bvalid, rvalid, rdata,
             m_axis_tready):
        c = self._comb
        # pre-edge captures (all syncs sample pre-edge regs)
        _flag_pre = self.sts_sync_flag
        _en_pre = self.cfg_enable_reg
        _rst_reg_pre = self.cfg_reset_reg
        _cnt_pre = self.sts_sync_count
        _preg = self.sts_hdr_parity_err_reg
        # ---- cfg regs ----
        if self.cfg_enable_reg:
            if cfg_reset:
                self.cfg_enable_reg = 0
        else:
            if cfg_enable:
                self.cfg_enable_reg = 1
            self.cfg_fifo_base_addr_reg = cfg_base_addr & 0xFFFFFFFF
            self.cfg_fifo_size_mask_reg = cfg_size_mask & 0xFFFF
        self.cfg_reset_reg = cfg_reset
        if rst:
            self.cfg_enable_reg = 0
            self.cfg_reset_reg = 0

        # ---- status sync (m_axis_clk domain; samples PRE-edge dec) ----
        hdr_parity_int = c["dec_hdr_parity_err"]
        self.sts_hdr_parity_err_reg = 0
        if self.sts_hdr_parity_err_cnt:
            self.sts_hdr_parity_err_reg = 1
            self.sts_hdr_parity_err_cnt = (self.sts_hdr_parity_err_cnt - 1) \
                & 0xF
        if hdr_parity_int:
            self.sts_hdr_parity_err_cnt = 0xF
        if rst:
            self.sts_hdr_parity_err_cnt = 0
            self.sts_hdr_parity_err_reg = 0

        # ---- status sync (clk domain) ----
        self.sts_sync_count = (_cnt_pre + 1) & 0x7
        if _cnt_pre == 0:
            self.sts_sync_flag = 1 if not _flag_pre else 0
            occ_int = (self.ch[0]["sts_occupancy_reg"] |
                       (self.ch[1]["sts_occupancy_reg"] << 17))
            self.sts_fifo_occupancy_sync = occ_int
        empty_int = 0
        full_int = 0
        reset_int = 0
        active_int = 0
        for ch in range(AXI_CH):
            empty_int |= c["raw_wr_out"][ch]["sts_fifo_empty"] << ch
            full_int |= c["raw_wr_out"][ch]["sts_fifo_full"] << ch
            reset_int |= self.raw[ch].fifo_reset_reg << ch
            active_int |= self.raw[ch].fifo_enable_reg << ch
        _e1 = self.sts_fifo_empty_sync_1
        _f1 = self.sts_fifo_full_sync_1
        _r1 = self.sts_reset_sync_1
        _a1 = self.sts_active_sync_1
        _p1 = self.sts_hdr_parity_err_sync_1
        self.sts_fifo_empty_sync_1 = empty_int
        self.sts_fifo_empty_sync_2 = _e1
        self.sts_fifo_full_sync_1 = full_int
        self.sts_fifo_full_sync_2 = _f1
        self.sts_reset_sync_1 = reset_int
        self.sts_reset_sync_2 = _r1
        self.sts_active_sync_1 = active_int
        self.sts_active_sync_2 = _a1
        self.sts_hdr_parity_err_sync_1 = _preg
        self.sts_hdr_parity_err_sync_2 = _p1

        # per-channel status/occupancy sync (pre-edge samples)
        for ch in range(AXI_CH):
            cc = self.ch[ch]
            _c1 = cc["cfg_enable_sync_1"]
            _r1 = cc["cfg_reset_sync_1"]
            _f1 = cc["sts_flag_sync_1"]
            _f2 = cc["sts_flag_sync_2"]
            _f3 = cc["sts_flag_sync_3"]
            cc["cfg_enable_sync_1"] = _en_pre
            cc["cfg_enable_sync_2"] = _c1
            cc["cfg_reset_sync_1"] = _rst_reg_pre
            cc["cfg_reset_sync_2"] = _r1
            cc["sts_flag_sync_1"] = _flag_pre
            cc["sts_flag_sync_2"] = _f1
            cc["sts_flag_sync_3"] = _f2
            if _f3 ^ _f2:
                occ = (self.raw_wr[ch].wr_start_ptr -
                       self.raw_rd[ch].rd_finish_ptr) & 0x1FFFF
                cc["sts_occupancy_reg"] = occ

        # ---- edge the raw modules (capture the raw module's PRE-EDGE
        # fifo_reset/fifo_enable/base/mask first, since raw_wr/raw_rd sample
        # those at this edge) ----
        # next-level values for the async-set chains (R(t+1) = L(t) | L(t+1))
        rst_req_in_next = 0
        for ch in range(AXI_CH):
            rst_req_in_next |= rst | self.ch[ch]["cfg_reset_sync_1"]
        for ch in range(AXI_CH):
            rmod = self.raw[ch]
            rmod._pre_reset = rmod.fifo_reset_reg
            rmod._pre_enable = rmod.fifo_enable_reg
            rmod._pre_base = rmod.fifo_base_addr_reg
            rmod._pre_mask = rmod.fifo_size_mask_reg
            self.raw[ch].edge(rst,
                              cfg_reset_next=self.ch[ch]["cfg_reset_sync_1"],
                              rst_req_in_next=rst_req_in_next)
            self.raw_wr[ch].edge(
                input_valid=c["ch_input_valid"][ch],
                input_data=(c["ch_input_data"] >> (32 * ch)) & 0xFFFFFFFF,
                rst=rst, cfg_reset=rmod._pre_reset,
                input_rst=rst, cfg_reset_next=rmod._fifo_reset_next)
            self.raw_rd[ch].edge(
                rvalid=rvalid[ch], rdata=rdata[ch],
                output_ready=(c["dec_out"]["input_ready"] >> ch) & 1,
                output_ctrl_ready=(c["dec_out"]["input_ctrl_ready"] >>
                                   ch) & 1,
                rst=rst, cfg_reset=rmod._pre_reset,
                output_rst=rst, cfg_reset_next=rmod._fifo_reset_next)

        # encoder edge
        self.enc.edge(rst, c["s_axis_rst_out"])
        # decoder edge
        self.dec.edge(rst, c["m_axis_rst_out"], m_axis_tready)
        self._comb = None


class AxivfifoPublic:
    """Black-box simulator for axivfifo_public (mirrors dut/axivfifo_top.v)."""

    DATA_WIDTH = AXI_DATA_WIDTH
    ADDR_WIDTH = AXI_ADDR_WIDTH
    DEPTH = 64          # WRITE_FIFO_DEPTH (window size is runtime-config)

    WR_IDLE, WR_WBEATS, WR_BRESP = 0, 1, 2
    RD_IDLE, RD_RBEATS = 0, 1

    def __init__(self,
                 len_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.len_ok_set = ([int(v) & 0xFF for v in len_ok_set]
                           if len_ok_set else list(PLACEHOLDER_LEN_OK_SET))
        while len(self.len_ok_set) < 4:
            self.len_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self._in = {
            "ch_sel": 0, "valid_pulse": 0, "addr": 0, "wd": 0,
            "wstrb": 0, "last": 0, "aw_ar": 0, "aw_ready": 0, "ar_ready": 0,
            "cfg_wr": 0, "cfg_sel": 0, "cfg_d0": 0, "cfg_d1": 0, "rst_n": 1,
        }
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, len_ok_set: List[int], done_hold_n: int):
        self.len_ok_set = [int(v) & 0xFF for v in len_ok_set]
        while len(self.len_ok_set) < 4:
            self.len_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # wrapper state (RTL declaration initializers)
        self.cfg_base_lo = 0
        self.cfg_base_hi = 0
        self.cfg_mask_lo = 0
        self.cfg_mask_hi = 0
        self.en_reg = 0
        self.s_pend = 0
        self.s_data = 0
        self.s_last = 0
        self.s_tkeep = 0
        self.s_pend2 = 0
        self.s_data2 = 0
        self.s_last2 = 0
        self.s_tkeep2 = 0
        self.aw_enq_pending = 0
        self.aw_enq_len = 0
        self.resp_wr_state = [self.WR_IDLE, self.WR_IDLE]
        self.wr_addr = [0, 0]
        self.wr_cnt = [0, 0]
        self.resp_rd_state = [self.RD_IDLE, self.RD_IDLE]
        self.rd_addr = [0, 0]
        self.rd_len = [0, 0]
        self.rd_cnt = [0, 0]
        self.mem0 = [0] * 16384
        self.mem1 = [0] * 16384
        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0
        self.trig_class_reg = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        self.cov_wr_beats = 0
        self.cov_rd_beats = 0
        self.cov_len = 0
        self.cov_addr = 0
        self.cov_wdata = 0
        self.cov_rdata = 0
        self.cov_wstrb = 0
        self.cov_sdata = 0
        self.cov_slast = 0
        self.cov_mdata = 0
        self.cov_mlast = 0
        self.cov_rd_wr = 0
        self.cov_cfg_ok = 0
        self.s1_stage = 0
        self.s2_armed = 0
        self.s3_armed = 0
        self.s4_gap = 0
        self.s4_chain = 0
        self.s4_link = 0
        self.s5_cnt = 0
        self.s7_cnt = 0
        self.s8_cnt = 0
        self.s9_cnt = 0
        self.s10_cnt = 0
        self.s10_armed = 0
        self._seq = {("cov_seq%d" % i): 0 for i in range(1, 13)}
        self.vf = Vfifo()
        # 4 reset cycles (rst_n=0) to match the Verilator preamble exactly.
        # NOTE: in the Verilator build the first preamble clock edge is
        # consumed by the initial settle, so sts_sync_count ends at 3 while
        # every other register behaves like 4 full reset cycles.
        for _ in range(4):
            self._cycle_rst()
        self.vf.sts_sync_count = 3

    # ------------------------------------------------------------------
    def apply_action(self, addr=0, ch_sel=0, aw_ar=0, valid_pulse=0, last=0,
                     wd=0, wstrb=0, aw_ready=0, ar_ready=0, cfg_wr=0,
                     cfg_sel=0, cfg_d0=0, cfg_d1=0, rst_n=1):
        self._in = {
            "ch_sel": int(ch_sel) & 7,
            "valid_pulse": int(valid_pulse) & 1,
            "addr": int(addr) & 0xFFFF,
            "wd": int(wd) & 0xFFFF,
            "wstrb": int(wstrb) & 0xF,
            "last": int(last) & 1,
            "aw_ar": int(aw_ar) & 1,
            "aw_ready": int(aw_ready) & 1,
            "ar_ready": int(ar_ready) & 1,
            "cfg_wr": int(cfg_wr) & 1,
            "cfg_sel": int(cfg_sel) & 3,
            "cfg_d0": int(cfg_d0) & 0xFF,
            "cfg_d1": int(cfg_d1) & 0xFF,
            "rst_n": int(rst_n) & 1,
        }

    def set_pins(self, aw_ar: Optional[int] = None,
                 aw_ready: Optional[int] = None,
                 ar_ready: Optional[int] = None):
        if aw_ar is not None:
            self._in["aw_ar"] = int(aw_ar) & 1
        if aw_ready is not None:
            self._in["aw_ready"] = int(aw_ready) & 1
        if ar_ready is not None:
            self._in["ar_ready"] = int(ar_ready) & 1

    # ------------------------------------------------------------------
    def _cycle_rst(self):
        """One cycle with rst=1 (reset preamble)."""
        self._step_impl(rst=1)

    def step(self):
        self._step_impl(rst=1 if not self._in.get("rst_n", 1) else 0)

    def _step_impl(self, rst):
        i = self._in
        # ---- action decode ----
        s_action = 1 if (i["ch_sel"] == 0) and i["valid_pulse"] and \
            not i["cfg_wr"] else 0
        m_action = 1 if (i["ch_sel"] == 1) and i["valid_pulse"] and \
            not i["cfg_wr"] else 0
        en_action = 1 if (i["ch_sel"] == 2) and i["valid_pulse"] and \
            not i["cfg_wr"] else 0
        rst_action = 1 if (i["ch_sel"] == 3) and i["valid_pulse"] and \
            not i["cfg_wr"] else 0
        cfg_action = 1 if i["cfg_wr"] and not i["valid_pulse"] else 0

        s_axis_tdata_in = ((i["cfg_d1"] << 24) | (i["cfg_d0"] << 16) |
                           (i["wd"] & 0xFFFF)) & 0xFFFFFFFF

        # ---- responder comb ----
        awready = [1 if (i["aw_ready"] and
                         self.resp_wr_state[ch] == self.WR_IDLE) else 0
                   for ch in range(AXI_CH)]
        wready = [i["aw_ar"]] * AXI_CH
        arready = [1 if (i["ar_ready"] and
                         self.resp_rd_state[ch] == self.RD_IDLE) else 0
                   for ch in range(AXI_CH)]
        bvalid = [1 if self.resp_wr_state[ch] == self.WR_BRESP else 0
                  for ch in range(AXI_CH)]
        rvalid = [1 if self.resp_rd_state[ch] == self.RD_RBEATS else 0
                  for ch in range(AXI_CH)]
        rdata = []
        for ch in range(AXI_CH):
            ba = (self.rd_addr[ch] + (self.rd_cnt[ch] << 2)) & 0xFFFF
            mem = self.mem0 if ch == 0 else self.mem1
            rdata.append(mem[ba >> 2])

        m_axis_tready = 1 if (i["aw_ar"] or m_action) else 0

        # ---- vfifo comb ----
        vout = self.vf.comb(
            s_tvalid=self.s_pend, s_tdata=self.s_data,
            s_tkeep=self.s_tkeep, s_tlast=self.s_last,
            m_axis_tready=m_axis_tready,
            awready=awready, arready=arready, wready=wready,
            bvalid=bvalid, rvalid=rvalid, rdata=rdata, rst=rst)
        s_axis_tready = vout["s_axis_tready"]
        m_axis_tvalid = vout["m_axis_tvalid"]
        m_axis_tdata = vout["m_axis_tdata"]
        m_axis_tlast = vout["m_axis_tlast"]
        m_axi_awvalid = vout["m_axi_awvalid"]
        m_axi_wvalid = vout["m_axi_wvalid"]
        m_axi_wlast = vout["m_axi_wlast"]
        m_axi_bready = vout["m_axi_bready"]
        m_axi_arvalid = vout["m_axi_arvalid"]
        m_axi_rready = vout["m_axi_rready"]
        sts_occ = vout["sts_fifo_occupancy"]
        sts_empty = vout["sts_fifo_empty"]
        sts_full = vout["sts_fifo_full"]
        sts_active = vout["sts_active"]
        sts_reset = vout["sts_reset"]

        # ---- wrapper handshakes (channel 0) ----
        aw_hs = 1 if (m_axi_awvalid[0] and awready[0]) else 0
        w_hs = 1 if (m_axi_wvalid[0] and wready[0]) else 0
        b_hs = 1 if (bvalid[0] and m_axi_bready[0]) else 0
        ar_hs = 1 if (m_axi_arvalid[0] and arready[0]) else 0
        r_hs = 1 if (rvalid[0] and m_axi_rready[0]) else 0
        s_hs = 1 if (self.s_pend and s_axis_tready) else 0
        m_hs = 1 if (m_axis_tvalid and m_axis_tready) else 0

        # ---- hidden trigger ----
        lok = self.len_ok_set
        el = self.aw_enq_len
        len_m = [1 if (lok[k] != 0 and el == lok[k]) else 0
                 for k in range(4)]
        trig = 1 if (w_hs and m_axi_wlast[0] and self.aw_enq_pending and
                     any(len_m)) else 0
        trig_class = next((k for k in range(4) if len_m[k]), 3)
        self._last_trig = trig
        self._last_w_hs = w_hs

        # pre-edge cfg snapshot for the vfifo's edge (the wrapper's cfg regs
        # commit AFTER the vfifo edge in the RTL's edge ordering)
        _cfg_base_pre_edge = ((self.cfg_base_hi << 8) | self.cfg_base_lo) & \
            0xFFFF
        _cfg_mask_pre_edge = ((self.cfg_mask_hi << 8) | self.cfg_mask_lo) & \
            0xFFFF

        # ---- cfg gating ----
        idle_all = 1 if (not self.s_pend and not self.s_pend2 and
                         not self.aw_enq_pending and
                         self.resp_wr_state[0] == self.WR_IDLE and
                         self.resp_wr_state[1] == self.WR_IDLE and
                         self.resp_rd_state[0] == self.RD_IDLE and
                         self.resp_rd_state[1] == self.RD_IDLE and
                         sts_occ == 0 and not m_axis_tvalid and
                         not self.cov_hold and not self.en_reg) else 0
        cfg_enable_pulse = 1 if (en_action and idle_all) else 0
        cfg_reset_pulse = 1 if (rst_action and not self.cov_hold) else 0

        # ---- busy / backpressure (comb) ----
        wr_act = 1 if (self.resp_wr_state[0] != self.WR_IDLE or
                       self.resp_wr_state[1] != self.WR_IDLE) else 0
        rd_act = 1 if (self.resp_rd_state[0] != self.RD_IDLE or
                       self.resp_rd_state[1] != self.RD_IDLE) else 0
        busy = 1 if (self.s_pend or self.s_pend2 or self.aw_enq_pending or
                     wr_act or rd_act or sts_occ != 0 or m_axis_tvalid) \
            else 0
        any_awv = 1 if (m_axi_awvalid[0] or m_axi_awvalid[1]) else 0
        all_awr = 1 if (awready[0] and awready[1]) else 0
        any_wv = 1 if (m_axi_wvalid[0] or m_axi_wvalid[1]) else 0
        any_arv = 1 if (m_axi_arvalid[0] or m_axi_arvalid[1]) else 0
        all_arr = 1 if (arready[0] and arready[1]) else 0
        any_rv = 1 if (rvalid[0] or rvalid[1]) else 0
        all_rr = 1 if (m_axi_rready[0] and m_axi_rready[1]) else 0
        bp = 1 if ((self.s_pend and not s_axis_tready) or
                   (any_awv and not all_awr) or
                   (any_wv and not i["aw_ar"]) or
                   (any_arv and not all_arr) or
                   (any_rv and not all_rr) or
                   (m_axis_tvalid and not m_axis_tready)) else 0
        idle_c = 1 if (not busy and not self.cov_hold) else 0
        full = 1 if (sts_full != 0) else 0
        empty = 1 if (sts_empty == 0x3) else 0

        cov_state = (3 if (wr_act and rd_act) else
                     (1 if wr_act else (2 if rd_act else 0)))

        # ---- wrapper edge (before vfifo edge: pre-edge reg reads) ----
        # S latch
        n_s_pend, n_s_data, n_s_last, n_s_tkeep = \
            self.s_pend, self.s_data, self.s_last, self.s_tkeep
        n_s_pend2, n_s_data2, n_s_last2, n_s_tkeep2 = \
            self.s_pend2, self.s_data2, self.s_last2, self.s_tkeep2
        if s_hs:
            if self.s_pend2:
                n_s_pend, n_s_data, n_s_last, n_s_tkeep = \
                    1, self.s_data2, self.s_last2, self.s_tkeep2
                n_s_pend2 = 0
            elif s_action and not self.cov_hold and not trig:
                n_s_pend, n_s_data, n_s_last, n_s_tkeep = \
                    1, s_axis_tdata_in, i["last"], i["wstrb"]
            else:
                n_s_pend = 0
        elif s_action and not self.cov_hold and not trig:
            if not self.s_pend:
                n_s_pend, n_s_data, n_s_last, n_s_tkeep = \
                    1, s_axis_tdata_in, i["last"], i["wstrb"]
            elif not self.s_pend2:
                n_s_pend2, n_s_data2, n_s_last2, n_s_tkeep2 = \
                    1, s_axis_tdata_in, i["last"], i["wstrb"]

        # aw_enq window
        n_aw_enq_pending, n_aw_enq_len = self.aw_enq_pending, self.aw_enq_len
        if aw_hs:
            n_aw_enq_pending = 1
            n_aw_enq_len = self.vf.raw_wr[0].awlen & 0xFF
        elif w_hs and m_axi_wlast[0]:
            n_aw_enq_pending = 0

        # cfg
        n_cfg_ok = 0
        n_base_lo, n_base_hi = self.cfg_base_lo, self.cfg_base_hi
        n_mask_lo, n_mask_hi = self.cfg_mask_lo, self.cfg_mask_hi
        n_en_reg = self.en_reg
        if cfg_action and idle_all:
            n_cfg_ok = 1
            sel = i["cfg_sel"]
            if sel == 0:
                n_base_lo = i["cfg_d0"]
            elif sel == 1:
                n_base_hi = i["cfg_d0"]
            elif sel == 2:
                n_mask_lo = i["cfg_d0"]
            elif sel == 3:
                n_mask_hi = i["cfg_d0"]
        if cfg_enable_pulse:
            n_en_reg = 1
            n_cfg_ok = 1
        if cfg_reset_pulse:
            n_en_reg = 0
            n_cfg_ok = 1

        # responders (pre-edge)
        n_resp_wr = list(self.resp_wr_state)
        n_wr_addr = list(self.wr_addr)
        n_wr_cnt = list(self.wr_cnt)
        n_resp_rd = list(self.resp_rd_state)
        n_rd_addr = list(self.rd_addr)
        n_rd_len = list(self.rd_len)
        n_rd_cnt = list(self.rd_cnt)
        mem_writes = []  # (ch, index, new value)
        for ch in range(AXI_CH):
            aw_hs_c = 1 if (m_axi_awvalid[ch] and awready[ch]) else 0
            if n_resp_wr[ch] == self.WR_IDLE:
                if aw_hs_c:
                    n_wr_addr[ch] = self.vf.raw_wr[ch].awaddr & 0xFFFF
                    n_wr_cnt[ch] = 0
                    n_resp_wr[ch] = self.WR_WBEATS
            elif n_resp_wr[ch] == self.WR_WBEATS:
                w_hs_ch = 1 if (m_axi_wvalid[ch] and wready[ch]) else 0
                if w_hs_ch:
                    ba = (self.wr_addr[ch] + (self.wr_cnt[ch] << 2)) & 0xFFFF
                    mem = self.mem0 if ch == 0 else self.mem1
                    wd = self.vf.raw_wr[ch].wdata & 0xFFFFFFFF
                    ws = self.vf.raw_wr[ch].wstrb & 0xF
                    wmask = 0
                    for b in range(4):
                        if (ws >> b) & 1:
                            wmask |= 0xFF << (8 * b)
                    old = mem[ba >> 2]
                    mem_writes.append((ch, ba >> 2,
                                       (old & ~wmask) | (wd & wmask)))
                    if m_axi_wlast[ch]:
                        n_resp_wr[ch] = self.WR_BRESP
                    else:
                        n_wr_cnt[ch] = (self.wr_cnt[ch] + 1) & 0xFF
            else:  # BRESP
                if bvalid[ch] and m_axi_bready[ch]:
                    n_resp_wr[ch] = self.WR_IDLE

            if n_resp_rd[ch] == self.RD_IDLE:
                if 1 if (m_axi_arvalid[ch] and arready[ch]) else 0:
                    n_rd_addr[ch] = self.vf.raw_rd[ch].araddr & 0xFFFF
                    n_rd_len[ch] = self.vf.raw_rd[ch].arlen & 0xFF
                    n_rd_cnt[ch] = 0
                    n_resp_rd[ch] = self.RD_RBEATS
            else:
                if rvalid[ch] and m_axi_rready[ch]:
                    if self.rd_cnt[ch] == self.rd_len[ch]:
                        n_resp_rd[ch] = self.RD_IDLE
                    else:
                        n_rd_cnt[ch] = (self.rd_cnt[ch] + 1) & 0xFF

        # hold FSM
        n_hld_state, n_hld_cnt = self.hld_state, self.hld_cnt
        n_hld_class, n_trig_class = self.hld_class, self.trig_class_reg
        n_hold = self.cov_hold
        n_done_ok_valid = 0
        n_done_ok_class = self.cov_done_ok_class
        if self.hld_state == 0:
            if trig:
                n_hld_state = 1
                n_hld_cnt = self.done_hold_n
                n_hld_class = trig_class
                n_trig_class = trig_class
                n_hold = 1
        elif self.hld_state == 1:
            if self.hld_cnt == 1:
                n_done_ok_valid = 1
                n_done_ok_class = self.hld_class
                n_hld_state = 2
                n_hold = 0
            else:
                n_hld_cnt = (self.hld_cnt - 1) & 0xFFFF
        else:
            n_hld_state = 0
            n_hold = 0

        # cov latches
        n_cov_wr_beats = self.cov_wr_beats
        if aw_hs:
            n_cov_wr_beats = 0
        elif w_hs and self.cov_wr_beats != 0xFF:
            n_cov_wr_beats = (self.cov_wr_beats + 1) & 0xFF
        n_cov_rd_beats = self.cov_rd_beats
        if ar_hs:
            n_cov_rd_beats = 0
        elif r_hs and self.cov_rd_beats != 0xFF:
            n_cov_rd_beats = (self.cov_rd_beats + 1) & 0xFF
        n_cov_len = self.cov_len
        if aw_hs:
            n_cov_len = self.vf.raw_wr[0].awlen & 0xFF
        elif ar_hs:
            n_cov_len = self.vf.raw_rd[0].arlen & 0xFF
        n_cov_addr = self.cov_addr
        if aw_hs:
            n_cov_addr = self.vf.raw_wr[0].awaddr & 0xFFFF
        elif ar_hs:
            n_cov_addr = self.vf.raw_rd[0].araddr & 0xFFFF
        n_cov_wdata, n_cov_wstrb = self.cov_wdata, self.cov_wstrb
        if w_hs:
            n_cov_wdata = self.vf.raw_wr[0].wdata & 0xFFFF
            n_cov_wstrb = self.vf.raw_wr[0].wstrb & 0xF
        n_cov_rdata = self.cov_rdata
        if r_hs:
            n_cov_rdata = rdata[0] & 0xFFFF
        n_cov_sdata, n_cov_slast = self.cov_sdata, self.cov_slast
        if s_hs:
            n_cov_sdata = self.s_data & 0xFF
            n_cov_slast = self.s_last
        n_cov_mdata, n_cov_mlast = self.cov_mdata, self.cov_mlast
        if m_hs:
            n_cov_mdata = m_axis_tdata & 0xFF
            n_cov_mlast = m_axis_tlast
        n_cov_rd_wr = self.cov_rd_wr
        if r_hs:
            n_cov_rd_wr = 1
        elif w_hs:
            n_cov_rd_wr = 0

        # seq monitors
        seq = {k: 0 for k in self._seq}
        n_s1 = self.s1_stage
        if aw_hs:
            n_s1 = 1
        elif self.s1_stage and w_hs and m_axi_wlast[0]:
            seq["cov_seq1"] = 1
            n_s1 = 0
        n_s2 = self.s2_armed
        if ar_hs:
            n_s2 = 1
        elif self.s2_armed and r_hs and (self.rd_cnt[0] == self.rd_len[0]):
            seq["cov_seq2"] = 1
            n_s2 = 0
        n_s3 = self.s3_armed
        if full:
            n_s3 = 1
        elif self.s3_armed and empty:
            seq["cov_seq3"] = 1
            n_s3 = 0
        n_s4_gap = self.s4_gap
        n_s4_chain = self.s4_chain
        n_s4_link = self.s4_link
        if b_hs:
            if self.s4_link and self.s4_chain < 15:
                n_s4_chain = (self.s4_chain + 1) & 0xF
            else:
                n_s4_chain = 1
            n_s4_link = 0
            n_s4_gap = 0
            if self.s4_link and self.s4_chain >= 2:
                seq["cov_seq4"] = 1
        elif self.s4_gap < 4:
            n_s4_gap = (self.s4_gap + 1) & 0xFF
        if aw_hs and 1 <= self.s4_gap <= 2:
            n_s4_link = 1
        n_s5 = self.s5_cnt
        if self.cov_hold:
            n_s5 = self.s5_cnt + 1 if self.s5_cnt < 0xFF else self.s5_cnt
            if self.s5_cnt >= 3:
                seq["cov_seq5"] = 1
        else:
            n_s5 = 0
        if self.hld_state == 1 and self.hld_cnt == 1:
            seq["cov_seq6"] = 1
        n_s7 = self.s7_cnt
        if m_axi_wvalid[0] and not wready[0]:
            n_s7 = self.s7_cnt + 1 if self.s7_cnt < 0xFF else self.s7_cnt
        else:
            n_s7 = 0
        if w_hs and self.s7_cnt >= 2:
            seq["cov_seq7"] = 1
        n_s8 = self.s8_cnt
        if busy:
            n_s8 = self.s8_cnt + 1 if self.s8_cnt < 0xFF else self.s8_cnt
            if self.s8_cnt >= 7:
                seq["cov_seq8"] = 1
        else:
            n_s8 = 0
        n_s9 = self.s9_cnt
        if idle_c:
            n_s9 = self.s9_cnt + 1 if self.s9_cnt < 0xFF else self.s9_cnt
            if self.s9_cnt >= 3:
                seq["cov_seq9"] = 1
        else:
            n_s9 = 0
        n_s10 = self.s10_cnt
        n_s10_armed = self.s10_armed
        if aw_hs and self.vf.raw_wr[0].awlen == 0:
            n_s10_armed = 1
            n_s10 = 0
        elif self.s10_armed and self.s10_cnt < 15:
            n_s10 = (self.s10_cnt + 1) & 0xF
        if w_hs and m_axi_wlast[0] and self.s10_armed and \
                self.s10_cnt <= 4:
            seq["cov_seq10"] = 1
            n_s10_armed = 0
        elif w_hs and m_axi_wlast[0]:
            n_s10_armed = 0
        if w_hs and m_axi_wlast[0] and self.aw_enq_len >= 8:
            seq["cov_seq11"] = 1
        if self.hld_state == 1 and self.hld_cnt == 1 and \
                self.hld_class == self.trig_class_reg:
            seq["cov_seq12"] = 1

        # ---- commit wrapper state ----
        if rst:
            self.s_pend = 0
            self.s_pend2 = 0
            self.aw_enq_pending = 0
            self.en_reg = 0
            self.cov_cfg_ok = 0
            self.resp_wr_state = [self.WR_IDLE, self.WR_IDLE]
            self.resp_rd_state = [self.RD_IDLE, self.RD_IDLE]
            self.wr_cnt = [0, 0]
            self.rd_cnt = [0, 0]
            self.hld_state = 0
            self.hld_cnt = 0
            self.hld_class = 0
            self.trig_class_reg = 0
            self.cov_hold = 0
            self.cov_done_ok_valid = 0
            self.cov_done_ok_class = 0
            self.cov_wr_beats = 0
            self.cov_rd_beats = 0
            self.cov_len = 0
            self.cov_addr = 0
            self.cov_wdata = 0
            self.cov_rdata = 0
            self.cov_wstrb = 0
            self.cov_sdata = 0
            self.cov_slast = 0
            self.cov_mdata = 0
            self.cov_mlast = 0
            self.cov_rd_wr = 0
            self.s1_stage = 0
            self.s2_armed = 0
            self.s3_armed = 0
            self.s4_gap = 0
            self.s4_chain = 0
            self.s4_link = 0
            self.s5_cnt = 0
            self.s7_cnt = 0
            self.s8_cnt = 0
            self.s9_cnt = 0
            self.s10_cnt = 0
            self.s10_armed = 0
            self._seq = {k: 0 for k in self._seq}
        else:
            self.s_pend = n_s_pend
            self.s_data = n_s_data
            self.s_last = n_s_last
            self.s_tkeep = n_s_tkeep
            self.s_pend2 = n_s_pend2
            self.s_data2 = n_s_data2
            self.s_last2 = n_s_last2
            self.s_tkeep2 = n_s_tkeep2
            self.aw_enq_pending = n_aw_enq_pending
            self.aw_enq_len = n_aw_enq_len
            self.cov_cfg_ok = n_cfg_ok
            self.cfg_base_lo = n_base_lo
            self.cfg_base_hi = n_base_hi
            self.cfg_mask_lo = n_mask_lo
            self.cfg_mask_hi = n_mask_hi
            self.en_reg = n_en_reg
            self.resp_wr_state = n_resp_wr
            self.wr_addr = n_wr_addr
            self.wr_cnt = n_wr_cnt
            self.resp_rd_state = n_resp_rd
            self.rd_addr = n_rd_addr
            self.rd_len = n_rd_len
            self.rd_cnt = n_rd_cnt
            for ch, idx, val in mem_writes:
                if ch == 0:
                    self.mem0[idx] = val & 0xFFFFFFFF
                else:
                    self.mem1[idx] = val & 0xFFFFFFFF
            self.hld_state = n_hld_state
            self.hld_cnt = n_hld_cnt
            self.hld_class = n_hld_class
            self.trig_class_reg = n_trig_class
            self.cov_hold = n_hold
            self.cov_done_ok_valid = n_done_ok_valid
            self.cov_done_ok_class = n_done_ok_class
            self.cov_wr_beats = n_cov_wr_beats
            self.cov_rd_beats = n_cov_rd_beats
            self.cov_len = n_cov_len
            self.cov_addr = n_cov_addr
            self.cov_wdata = n_cov_wdata
            self.cov_rdata = n_cov_rdata
            self.cov_wstrb = n_cov_wstrb
            self.cov_sdata = n_cov_sdata
            self.cov_slast = n_cov_slast
            self.cov_mdata = n_cov_mdata
            self.cov_mlast = n_cov_mlast
            self.cov_rd_wr = n_cov_rd_wr
            self.s1_stage = n_s1
            self.s2_armed = n_s2
            self.s3_armed = n_s3
            self.s4_gap = n_s4_gap
            self.s4_chain = n_s4_chain
            self.s4_link = n_s4_link
            self.s5_cnt = n_s5
            self.s7_cnt = n_s7
            self.s8_cnt = n_s8
            self.s9_cnt = n_s9
            self.s10_cnt = n_s10
            self.s10_armed = n_s10_armed
            self._seq = seq

        # ---- vfifo edge ----
        # NOTE: the RTL's vfifo samples the wrapper's PRE-EDGE cfg regs and
        # the base is REPLICATED per channel ({base, base}).
        cfg_base_pre = _cfg_base_pre_edge
        cfg_base = cfg_base_pre | (cfg_base_pre << 16)
        self.vf.edge(cfg_base, _cfg_mask_pre_edge, cfg_enable_pulse,
                     cfg_reset_pulse, rst, awready, arready, wready, bvalid,
                     rvalid, rdata, m_axis_tready)

        # ---- post-edge comb echoes (read back after the edge, like the
        # Verilator tb reading at clk=0) ----
        wr_act_p = 1 if (self.resp_wr_state[0] != self.WR_IDLE or
                         self.resp_wr_state[1] != self.WR_IDLE) else 0
        rd_act_p = 1 if (self.resp_rd_state[0] != self.RD_IDLE or
                         self.resp_rd_state[1] != self.RD_IDLE) else 0
        cov_state_p = (3 if (wr_act_p and rd_act_p) else
                       (1 if wr_act_p else (2 if rd_act_p else 0)))
        sts_occ_p = self.vf.sts_fifo_occupancy_sync
        m_axis_tvalid_p = self.vf.dec.m_axis_tvalid
        s_axis_rst_out_p = 1 if any(
            w.rst_sync_3 for w in self.vf.raw_wr) else 0
        tready_p = self.vf.enc.tready(s_axis_rst_out_p)
        busy_p = 1 if (self.s_pend or self.s_pend2 or
                       self.aw_enq_pending or wr_act_p or rd_act_p or
                       sts_occ_p != 0 or m_axis_tvalid_p) else 0
        awready_p = [1 if (i["aw_ready"] and
                           self.resp_wr_state[ch] == self.WR_IDLE) else 0
                     for ch in range(AXI_CH)]
        arready_p = [1 if (i["ar_ready"] and
                           self.resp_rd_state[ch] == self.RD_IDLE) else 0
                     for ch in range(AXI_CH)]
        rvalid_p = [1 if self.resp_rd_state[ch] == self.RD_RBEATS else 0
                    for ch in range(AXI_CH)]
        rready_p = []
        for ch in range(AXI_CH):
            rr = self.vf.raw_rd[ch]
            full_p = 1 if rr.read_fifo_wr_ptr_gray == \
                ((rr.rd_ptr_gray_sync_2 ^ 0x80) & 0xFF) else 0
            cfull_p = 1 if rr.read_fifo_wr_ptr_gray == \
                ((rr.ctrl_rd_ptr_gray_sync_2 ^ 0x80) & 0xFF) else 0
            rready_p.append(1 if (not full_p and not cfull_p) else 0)
        any_awv_p = 1 if (self.vf.raw_wr[0].awvalid or
                          self.vf.raw_wr[1].awvalid) else 0
        all_awr_p = 1 if (awready_p[0] and awready_p[1]) else 0
        any_wv_p = 1 if (self.vf.raw_wr[0].wvalid or
                         self.vf.raw_wr[1].wvalid) else 0
        any_arv_p = 1 if (self.vf.raw_rd[0].arvalid or
                          self.vf.raw_rd[1].arvalid) else 0
        all_arr_p = 1 if (arready_p[0] and arready_p[1]) else 0
        any_rv_p = 1 if (rvalid_p[0] or rvalid_p[1]) else 0
        all_rr_p = 1 if (rready_p[0] and rready_p[1]) else 0
        m_tready_p = 1 if (i["aw_ar"] or m_action) else 0
        bp_p = 1 if ((self.s_pend and not tready_p) or
                     (any_awv_p and not all_awr_p) or
                     (any_wv_p and not i["aw_ar"]) or
                     (any_arv_p and not all_arr_p) or
                     (any_rv_p and not all_rr_p) or
                     (m_axis_tvalid_p and not m_tready_p)) else 0
        full_p = 1 if self.vf.sts_fifo_full_sync_2 != 0 else 0
        empty_p = 1 if self.vf.sts_fifo_empty_sync_2 == 0x3 else 0

        self._busy = busy_p
        self._bp = bp_p
        self._full = full_p
        self._empty = empty_p
        self._cov_state = cov_state_p
        self._cov_level = (((sts_occ_p >> 2) & 0x7FFF) +
                           ((sts_occ_p >> 19) & 0x7FFF)) & 0x7F

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_state": self._cov_state,
            "cov_wr_beats": self.cov_wr_beats,
            "cov_rd_beats": self.cov_rd_beats,
            "cov_len": self.cov_len,
            "cov_level": self._cov_level,
            "cov_addr": self.cov_addr,
            "cov_wdata": self.cov_wdata,
            "cov_rdata": self.cov_rdata,
            "cov_wstrb": self.cov_wstrb,
            "cov_sdata": self.cov_sdata,
            "cov_slast": self.cov_slast,
            "cov_mdata": self.cov_mdata,
            "cov_mlast": self.cov_mlast,
            "cov_mvalid": self.vf.dec.m_axis_tvalid,
            "cov_rd_wr": self.cov_rd_wr,
            "cov_busy": self._busy,
            "cov_bp": self._bp,
            "cov_full": self._full,
            "cov_empty": self._empty,
            "cov_cfg_ok": self.cov_cfg_ok,
            "cov_hold": self.cov_hold,
            "cov_done_ok_valid": self.cov_done_ok_valid,
            "cov_done_ok_class": self.cov_done_ok_class,
            "cov_seq1": self._seq["cov_seq1"],
            "cov_seq2": self._seq["cov_seq2"],
            "cov_seq3": self._seq["cov_seq3"],
            "cov_seq4": self._seq["cov_seq4"],
            "cov_seq5": self._seq["cov_seq5"],
            "cov_seq6": self._seq["cov_seq6"],
            "cov_seq7": self._seq["cov_seq7"],
            "cov_seq8": self._seq["cov_seq8"],
            "cov_seq9": self._seq["cov_seq9"],
            "cov_seq10": self._seq["cov_seq10"],
            "cov_seq11": self._seq["cov_seq11"],
            "cov_seq12": self._seq["cov_seq12"],
        }


def aw_hs_ch(is_ch0, m_axi_awvalid, awready, ch):  # noqa: F811 (unused)
    return 1 if (m_axi_awvalid[ch] and awready[ch]) else 0


if __name__ == "__main__":
    dut = AxivfifoPublic()
    print("axivfifo_public local_sim loaded")
