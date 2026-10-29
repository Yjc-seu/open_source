#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axicdma_public - Coverage Simulator (VCS-equivalent, generic evaluator +
DUT-specific trackers).
Reads dut/coverage_meta.json and evaluates bins against a signals dict each
cycle, producing the same flat coverage vector the committee VCS covergroup
(dut/covergroup.svh) returns. Works unchanged on local_sim and Verilator
signal dictionaries (identical cov_* schema).

Generic part: basic / boundary / condition / temporal / cross / seq_hit bins
are evaluated straight from coverage_meta.json against the signals dict.
DUT-specific part: the deep (ds_*) and sva (as_*) trackers mirror the RTL
trackers in dut/covergroup.svh and the cover properties in dut/assert_cov.svh
1:1.

Signal schema (sim_main header order, local_sim.read_signals 1:1):
  cov_state (0=IDLE 1=CFG 2=ADDR 3=DMA_RD 4=DMA_WR 5=DONE), cov_len,
  cov_addr_hi, cov_addr_lo, cov_beats_done, cov_rd_wr, cov_busy, cov_done,
  cov_status_err, cov_hold, cov_poll, cov_cfg_acc, cov_cfg_rej,
  cov_done_ok_valid, cov_done_ok_class, cov_seq1..cov_seq12
"""

import json
import os
from typing import Dict, List

import numpy as np

ST_IDLE = 0


class CoverageSimulator:
    def __init__(self, meta_path: str, done_hold_n: int = 16):
        with open(meta_path, "r", encoding="utf-8") as f:
            self.meta = json.load(f)
        self.coverpoints = self.meta["coverpoints"]
        # done_hold_n drives the parameter-keyed hold-window bins.
        self.done_hold_n = int(done_hold_n or 16)
        self.total_bins = 0
        self.reset()

    def reset(self) -> np.ndarray:
        """Reset all bin counts and return the zeroed coverage vector."""
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
        # deep ds_hold_window: hold run >= done_hold_n - 1
        self._ds_hold_run = 0
        self._ds_hold_max = 0
        self._ds_hold_hit = False
        # deep ds_class_switch: two done_ok pulses with distinct classes
        self._ds_class_first = None
        self._ds_class_switch = False
        # deep ds_len_diversity: >=4 distinct lens across completions
        self._ds_len_set = set()
        self._ds_len_hit = False
        # sva: busy streaks / active dwell
        self._busy_run = 0
        self._busy_max = 0
        # sva: hold dwell
        self._hold_run = 0
        self._hold_max = 0
        # sva: idle dwell (state == IDLE)
        self._idle_run = 0
        self._idle_max = 0

    def _update_trackers(self, signals: Dict):
        """Advance the cross-cycle trackers (mirrors covergroup.svh 1:1)."""
        state = int(signals.get("cov_state", 0) or 0)
        busy = int(signals.get("cov_busy", 0) or 0)
        hold = int(signals.get("cov_hold", 0) or 0)

        # ---- deep ds_hold_window: hold run length (parameter-driven) ----
        if hold == 1:
            self._ds_hold_run += 1
        else:
            self._ds_hold_run = 0
        if self._ds_hold_run > self._ds_hold_max:
            self._ds_hold_max = self._ds_hold_run
        if self._ds_hold_max >= self.done_hold_n - 1:
            self._ds_hold_hit = True

        # ---- deep ds_class_switch ----
        if signals.get("cov_done_ok_valid"):
            cls = int(signals.get("cov_done_ok_class", 0) or 0)
            if self._ds_class_first is None:
                self._ds_class_first = cls
            elif cls != self._ds_class_first:
                self._ds_class_switch = True

        # ---- deep ds_len_diversity: distinct lens at done pulses ----
        if signals.get("cov_done"):
            self._ds_len_set.add(int(signals.get("cov_len", 0) or 0))
        if len(self._ds_len_set) >= 4:
            self._ds_len_hit = True

        if self._ds_hold_hit:
            self._hit("ds_hold_window", "hold_window_hit")
        if self._ds_class_switch:
            self._hit("ds_class_switch", "class_switch_hit")
        if self._ds_len_hit:
            self._hit("ds_len_diversity", "len_div_hit")

        # ---- sva: busy streak + active dwell ----
        if busy == 1:
            self._busy_run += 1
            if self._busy_run > self._busy_max:
                self._busy_max = self._busy_run
        else:
            self._busy_run = 0
        for b in (2, 4, 8):
            if self._busy_max >= b:
                self._hit("as_busy_streak", "busy%d" % b)
        for b, name in ((1, "act1"), (8, "act8"), (16, "act16")):
            if self._busy_max >= b:
                self._hit("as_active_dwell", name)

        # ---- sva: hold dwell ----
        if hold == 1:
            self._hold_run += 1
            if self._hold_run > self._hold_max:
                self._hold_max = self._hold_run
        else:
            self._hold_run = 0
        if self._hold_max >= 4:
            self._hit("as_hold_dwell", "hold4")
        if self._hold_max >= self.done_hold_n - 1:
            self._hit("as_hold_dwell", "holdfull")

        # ---- sva: idle dwell (state == IDLE) ----
        if state == ST_IDLE:
            self._idle_run += 1
            if self._idle_run > self._idle_max:
                self._idle_max = self._idle_run
        else:
            self._idle_run = 0
        if self._idle_max >= 4:
            self._hit("as_idle_dwell", "idle4")
        if self._idle_max >= 16:
            self._hit("as_idle_dwell", "idle16")

    def _target_signal(self, cp) -> str:
        # primary signal name = comma-separated parent list, take first
        sig = cp.get("signal", "")
        return sig.split(",")[0].strip()

    def step(self, signals: Dict) -> np.ndarray:
        """Process one cycle of signals and update coverage."""
        for cp in self.coverpoints:
            t = cp["type"]
            if t == "cross":
                self._process_cross(cp, signals)
            elif t == "seq_hit":
                self._process_seq(cp, signals)
            elif t in ("deep", "sva"):
                pass  # cross-cycle trackers, advanced by _update_trackers
            else:
                self._process_leaf(cp, signals)
        self._update_trackers(signals)
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
        if isinstance(val, bool):
            val = 1 if val else 0
        val = int(val)
        if cp["type"] == "temporal":
            # requires the valid flag in the same cycle
            vflag = cp.get("valid_signal", "cov_done_ok_valid")
            if not signals.get(vflag, False):
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
        """Current coverage vector (Attachment-C C.2 compatible)."""
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
    print(f"Total bins: {sim.total_bins}")
