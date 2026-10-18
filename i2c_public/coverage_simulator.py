#!/usr/bin/env python3
"""
i2c_public - Coverage Simulator (VCS-equivalent, generic).
Reads dut/coverage_meta.json and evaluates bins against a signals dict each
cycle, producing the same flat coverage vector the committee VCS covergroup
(covergroup.svh) plus assert_cov.svh return.

The deep / sva tracker logic mirrors dut/covergroup.svh and dut/assert_cov.svh
1:1, so the identical code runs unchanged on the local_sim and Verilator
backends.
"""

import json
import os
from typing import Dict, List

import numpy as np


class CoverageSimulator:
    def __init__(self, meta_path: str, addr_hold_n: int = 16):
        with open(meta_path, "r", encoding="utf-8") as f:
            self.meta = json.load(f)
        self.coverpoints = self.meta["coverpoints"]
        # addr_hold_n drives the parameter-keyed deep-temporal hold-window bins.
        self.addr_hold_n = addr_hold_n
        # Parameter-adaptive hold window: the required dwell is
        # max(addr_hold_n - 1, 1), matching HOLD_WIN in covergroup.svh /
        # assert_cov.svh.
        self.hold_win = max(int(addr_hold_n) - 1, 1)
        self.total_bins = 0
        self.reset()

    def reset(self) -> np.ndarray:
        """Reset all bin counts and return the zeroed coverage vector.

        Attachment-C compatible: returns np.ndarray shape=(total_bins,),
        dtype float32.
        """
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

    # -- deep-temporal (cross-cycle) trackers -------------------------------
    def _reset_trackers(self):
        """Reset the cross-cycle tracker state (deep + sva coverpoints).

        These integrate information over many cycles: hold-window dwell
        length, addr_ok class ordering across completions, transaction
        address diversity, busy/write/read runs, and dwell lengths.
        """
        # deep: ds_hold_window -- longest run of cov_hold == 1 reached
        # (addr_hold_n - 1) cycles.
        self._ds_hold_run = 0
        self._ds_hold_max = 0
        self._ds_hold_hit = False
        # deep: ds_class_switch -- two addr_ok completions with distinct
        # classes.
        self._ds_class_first = None
        self._ds_class_switch = False
        # deep: ds_addr_diverse -- two transactions completed (stop ended)
        # with two distinct target addresses.
        self._ds_addr_seen = False
        self._ds_addr_first = None
        self._ds_addr_hit = False
        self._prev_bus_ctrl = 0
        # sva: consecutive busy run length
        self._sv_busy_run = 0
        self._sv_busy_max = 0
        # sva: consecutive write-data run length
        self._sv_wr_run = 0
        self._sv_wr_max = 0
        # sva: consecutive read-byte run length
        self._sv_rd_run = 0
        self._sv_rd_max = 0
        # sva: transaction-active (cov_state != IDLE) dwell
        self._sv_act_run = 0
        self._sv_act_max = 0
        # sva: hold dwell
        self._sv_hold_run = 0
        self._sv_hold_max = 0
        # sva: idle dwell (no busy / no bus control / no hold)
        self._sv_idle_run = 0
        self._sv_idle_max = 0

    def _update_deep_trackers(self, signals: Dict):
        """Advance the cross-cycle deep-temporal and sva trackers.

        Built purely from existing exported observation signals, so the same
        logic runs unchanged on both the local_sim and Verilator backends.
        """
        def sig(k, d=0):
            v = signals.get(k, d)
            if isinstance(v, bool):
                return 1 if v else 0
            return int(v or 0)

        hold = sig("cov_hold")

        # deep: hold-window dwell
        if hold == 1:
            self._ds_hold_run += 1
        else:
            self._ds_hold_run = 0
        if self._ds_hold_run > self._ds_hold_max:
            self._ds_hold_max = self._ds_hold_run
        if self._ds_hold_max >= self.hold_win:
            self._ds_hold_hit = True

        # deep: addr_ok class ordering across completions
        if sig("cov_addr_ok_valid"):
            cls = sig("cov_addr_ok_class")
            if self._ds_class_first is None:
                self._ds_class_first = cls
            elif cls != self._ds_class_first:
                self._ds_class_switch = True

        # deep: transaction address diversity (stop completion edge)
        bus_ctrl = sig("cov_bus_ctrl")
        txn_end = (self._prev_bus_ctrl == 1 and bus_ctrl == 0)
        if txn_end:
            addr = sig("cov_addr")
            if not self._ds_addr_seen:
                self._ds_addr_seen = True
                self._ds_addr_first = addr
            elif addr != self._ds_addr_first:
                self._ds_addr_hit = True
        self._prev_bus_ctrl = bus_ctrl

        if self._ds_hold_hit:
            self._hit("ds_hold_window", "hold_window_hit")
        if self._ds_class_switch:
            self._hit("ds_class_switch", "class_switch_hit")
        if self._ds_addr_hit:
            self._hit("ds_addr_diverse", "addr_diverse_hit")

        # sva: consecutive busy run
        busy = sig("cov_busy")
        if busy == 1:
            self._sv_busy_run += 1
            if self._sv_busy_run > self._sv_busy_max:
                self._sv_busy_max = self._sv_busy_run
        else:
            self._sv_busy_run = 0
        for b in (2, 4, 8):
            if self._sv_busy_max >= b:
                self._hit("sva_busy_streak", "run%d" % b)

        # sva: write / read runs; reset on address-phase accept (cov_state==
        # START the cycle after the accept), a real stop accept (bus_control=1,
        # busy=0) or transaction end.
        state = sig("cov_state")
        any_acc = sig("cov_any_acc")
        cmd = sig("cov_cmd")
        reset = (state == 1) or (any_acc and cmd == 4
                                 and bus_ctrl == 1 and busy == 0) or txn_end

        if sig("cov_wr_valid") == 1:
            self._sv_wr_run += 1
            if self._sv_wr_run > self._sv_wr_max:
                self._sv_wr_max = self._sv_wr_run
        elif reset:
            self._sv_wr_run = 0
        if self._sv_wr_max >= 3:
            self._hit("sva_wr_run", "wr_run3")

        if sig("cov_rd_valid") == 1:
            self._sv_rd_run += 1
            if self._sv_rd_run > self._sv_rd_max:
                self._sv_rd_max = self._sv_rd_run
        elif reset:
            self._sv_rd_run = 0
        if self._sv_rd_max >= 2:
            self._hit("sva_rd_run", "rd_run2")

        # sva: transaction-active dwell (cov_state != IDLE)
        if state != 0:
            self._sv_act_run += 1
            if self._sv_act_run > self._sv_act_max:
                self._sv_act_max = self._sv_act_run
        else:
            self._sv_act_run = 0
        for b, name in ((1, "dwell1"), (8, "dwell8"), (16, "dwell16")):
            if self._sv_act_max >= b:
                self._hit("sva_active_dwell", name)

        # sva: hold dwell
        if hold == 1:
            self._sv_hold_run += 1
            if self._sv_hold_run > self._sv_hold_max:
                self._sv_hold_max = self._sv_hold_run
        else:
            self._sv_hold_run = 0
        if self._sv_hold_max >= 4:
            self._hit("sva_hold_dwell", "hold4")
        if self._sv_hold_max >= self.hold_win:
            self._hit("sva_hold_dwell", "holdfull")

        # sva: idle dwell
        if busy == 0 and bus_ctrl == 0 and hold == 0:
            self._sv_idle_run += 1
            if self._sv_idle_run > self._sv_idle_max:
                self._sv_idle_max = self._sv_idle_run
        else:
            self._sv_idle_run = 0
        if self._sv_idle_max >= 4:
            self._hit("sva_idle_dwell", "idle4")
        if self._sv_idle_max >= 16:
            self._hit("sva_idle_dwell", "idle16")

    def _target_signal(self, cp) -> str:
        # primary signal name = comma-separated parent list, take first
        sig = cp.get("signal", "")
        return sig.split(",")[0].strip()

    def step(self, signals: Dict) -> np.ndarray:
        """Process one cycle of signals and update coverage.

        Attachment-C compatible: returns the current coverage vector as
        np.ndarray shape=(total_bins,), dtype float32.
        """
        for cp in self.coverpoints:
            t = cp["type"]
            if t == "cross":
                self._process_cross(cp, signals)
            elif t == "seq_hit":
                self._process_seq(cp, signals)
            elif t in ("deep", "sva"):
                pass  # cross-cycle trackers, advanced by _update_deep_trackers
            else:
                self._process_leaf(cp, signals)
        self._update_deep_trackers(signals)
        return self._vector()

    def _process_seq(self, cp, signals):
        """Sequence (SVA cover property) hit: bin fires when the named seq
        flag is 1 in this cycle."""
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
        # normalize for comparison
        if isinstance(val, bool):
            val = 1 if val else 0
        val = int(val)
        if cp["type"] == "temporal":
            # requires the associated valid pulse in the same cycle
            valid_sig = cp.get("valid", "cov_addr_ok_valid")
            if not signals.get(valid_sig, False):
                return
        for b in cp.get("bins", []):
            if int(b["value"]) == val:
                self._hit(name, b["name"])

    def _process_cross(self, cp, signals):
        name = cp["name"]
        parents = [s.strip() for s in cp.get("signal", "").split(",")]
        raw = [signals.get(p) for p in parents]
        if any(v is None for v in raw):
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
        """Coverage as a flat binary vector (1=hit, 0=not hit)."""
        return list(self._vector())

    def get_state(self) -> np.ndarray:
        """Current coverage vector (Attachment-C C.2 compatible).

        Same shape/dtype as reset()/step(): np.ndarray shape=(total_bins,),
        dtype float32, 1.0 = bin hit at least once, 0.0 = never hit.
        """
        return self._vector()

    def _vector(self) -> np.ndarray:
        """Current coverage as a flat binary vector, dtype float32."""
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
    sim = CoverageSimulator(os.path.join(here, "dut", "coverage_meta.json"))
    print("Total bins: %d" % sim.total_bins)
