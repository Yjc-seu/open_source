#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ethmacmii_public - timing_measure.py
=====================================
实测 MII 半字节时序：以真实 RTL（Verilator）的 mii_txd / mii_tx_en 线信号为
唯一依据，测量帧头（前导+SFD）、载荷、填充、FCS、IFG 的拍数，并校验线上
FCS 半字节流与 python CRC 参考一致。结果写入 spec §3。

用法（Linux/WSL，包根目录）：
    python3 timing_measure.py
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

from local_sim import ethernet_fcs_bytes  # noqa: E402
from verilator_harness.run_verilator import run_verilator_simulation  # noqa: E402


def idle_actions(n, tready=1):
    return [{"tx_tready": tready, "mii_rx_dv": 0} for _ in range(n)]


def send_actions(data, tready=1):
    out = []
    for b in data:
        out.append({"tx_byte": b, "tx_send": 1, "tx_tready": tready,
                    "mii_rx_dv": 0})
    return out


def measure_frame(data, label, cfg_ifg=None):
    A = [{"rst_n": 0}] * 1
    if cfg_ifg is not None:
        A += [{"cfg_wr": 1, "cfg_sel": 0, "cfg_d0": cfg_ifg, "tx_send": 0}]
        A += idle_actions(10)
    A += idle_actions(60)
    # frame 2 bytes are injected 20 cycles after frame 1's bytes: this lands
    # inside frame 1's PAD (after its frame boundary is decided), so frame 2
    # queues up and the measured en-fall -> en-rise gap is the pure IFG
    # (2 x cfg_ifg clocks).
    A += send_actions(data)
    A += idle_actions(20)
    A += send_actions(data)
    A += idle_actions(2000)
    res = run_verilator_simulation(A)
    sigs = res["signals"]

    # Extract the TX line trace from real-core signals only:
    # cov_mii_tx_en (top-level mii_tx_en, post phy register)
    en = [s["cov_mii_tx_en"] for s in sigs]
    txd = [s["cov_mii_txd"] for s in sigs]

    # find en active window
    starts = [i for i in range(1, len(en)) if en[i] == 1 and en[i - 1] == 0]
    if not starts:
        print(f"[{label}] no tx_en activity!")
        return None
    s0 = starts[0]
    # en falls at the end of FCS; find end
    ends = [i for i in range(s0 + 1, len(en)) if en[i] == 0 and en[i - 1] == 1]
    e0 = ends[0] if ends else len(en)
    frame_en = en[s0:e0]
    frame_nibs = txd[s0:e0]

    # split preamble / payload+pad / FCS
    n_pre = 16          # 8 bytes x 2 nibbles
    n_fcs = 8           # 4 bytes x 2 nibbles
    n_data = len(frame_en) - n_pre - n_fcs
    pre_nibs = frame_nibs[:n_pre]
    data_nibs = frame_nibs[n_pre:n_pre + n_data]
    fcs_nibs = frame_nibs[n_pre + n_data:]

    # reference FCS: data + pad (60 bytes total data, pad = 60 - len(data))
    pad = [0x00] * (60 - len(data))
    ref_data = list(data) + pad
    ref_fcs = byte_to_nibbles_ref(ethernet_fcs_bytes(bytes(ref_data)))

    pre_ok = (pre_nibs[:14] == [0x5] * 14 and pre_nibs[14:16] == [0x5, 0xD])
    data_ok = (data_nibs == byte_to_nibbles_ref(ref_data))
    fcs_ok = (fcs_nibs == ref_fcs)

    # IFG: time from frame-1 en fall to frame-2 en rise
    next_rise = [i for i in range(e0 + 1, len(en))
                 if en[i] == 1 and en[i - 1] == 0]
    ifg = (next_rise[0] - e0) if next_rise else None

    print(f"[{label}] en 高 {len(frame_en)} 拍 (前导 {n_pre} + 数据/填充 "
          f"{n_data} + FCS {n_fcs}); 前导校验 {pre_ok}; 数据校验 {data_ok}; "
          f"FCS 校验 {fcs_ok}; 帧间隔(IFG) {ifg} 拍")
    return {
        "en_cycles": len(frame_en), "n_pre": n_pre, "n_data": n_data,
        "n_fcs": n_fcs, "pre_ok": pre_ok, "data_ok": data_ok, "fcs_ok": fcs_ok,
        "ifg_cycles": ifg,
    }


def byte_to_nibbles_ref(data):
    out = []
    for b in data:
        out.append(b & 0xF)
        out.append((b >> 4) & 0xF)
    return out


def main():
    print("== MII 半字节实测（真实 RTL 线信号）==")
    r1 = measure_frame([0x11, 0x22], "2B 帧")
    r2 = measure_frame([0x5A], "1B 帧")
    # IFG 随 cfg_ifg 变化: cfg_ifg=1 -> 2 拍; cfg_ifg=255 -> 510 拍
    data = [0x11, 0x22]
    r3 = measure_frame(data, "cfg_ifg=1", cfg_ifg=1)
    r4 = measure_frame(data, "cfg_ifg=255", cfg_ifg=255)
    ifg1 = r3["ifg_cycles"] if r3 else None
    ifg255 = r4["ifg_cycles"] if r4 else None

    ok = (r1 and r2 and r1["pre_ok"] and r1["data_ok"] and r1["fcs_ok"]
          and r2["fcs_ok"] and r2["data_ok"]
          and r1["ifg_cycles"] == 24
          and ifg1 == 2 and ifg255 == 510)
    print("TIMING MEASURE", "OK" if ok else "CHECK VALUES ABOVE")


if __name__ == "__main__":
    main()
