#!/usr/bin/env python3
"""
axisadapter_public - Coverage Simulator (VCS-equivalent, generic evaluator +
DUT-specific trackers).
Reads dut/coverage_meta.json and evaluates bins against a signals dict each
cycle, producing the same flat coverage vector the committee VCS covergroup
(dut/covergroup.svh) returns. Works unchanged on local_sim and Verilator
signal dictionaries (identical cov_* schema).

Generic part: basic / boundary / condition / temporal / cross / seq_hit bins
are evaluated straight from coverage_meta.json against the signals dict.
Leaf coverpoints honour an optional "valid_signal" gate (frame/beat counters
and data latches are only meaningful on their completion pulses).
DUT-specific part: the deep (ds_hold_window_max / ds_class_switch /
ds_word_diversity) and sva trackers mirror the RTL-era trackers in
dut/covergroup.svh and the cover properties in dut/assert_cov.svh 1:1.
"""

import json
import os
from typing import Dict, List

import numpy as np


class CoverageSimulator:
    def __init__(self, meta_path: str, done_hold_n: int = 16):
        with open(meta_path, "r", encoding="utf-8") as f:
            self.meta = json.load(f)
        self.coverpoints = self.meta["coverpoints"]
        # done_hold_n drives the parameter-keyed hold-window bins
        # (ds_hold_window_max / timing_hold_dwell.holdfull).
        self.done_hold_n = int(done_hold_n or 16)
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

    # -- cross-cycle trackers (deep + sva) ----------------------------------
    def _reset_trackers(self):
        # deep: hold window length (parameter-driven)
        self._ds_hold_run = 0
        self._ds_hold_max = 0
        self._ds_hold_hit = False
        # deep: done_ok class switch
        self._ds_class_first = None
        self._ds_class_switch = False
        # deep: completed-frame word-count diversity (>=4 distinct values,
        # sampled on the m-side tlast handshake pulses of either adapter)
        self._ds_word_set = set()
        self._ds_word_hit = False
        # sva/dataflow: busy streak
        self._df_busy_run = 0
        self._df_busy_max = 0
        # sva/dataflow: active dwell (cov_state != IDLE)
        self._df_active_run = 0
        self._df_active_max = 0
        # sva/timing: hold dwell
        self._tp_hold_run = 0
        self._tp_hold_max = 0
        # sva/timing: idle dwell
        self._tp_idle_run = 0
        self._tp_idle_max = 0

    def _update_trackers(self, signals: Dict):
        """Advance the cross-cycle trackers (mirrors covergroup.svh 1:1)."""
        hold = int(signals.get("cov_hold", 0) or 0)
        busy = int(signals.get("cov_busy", 0) or 0)
        state = int(signals.get("cov_state", 0) or 0)

        # ---- deep: hold window length ----
        if hold == 1:
            self._ds_hold_run += 1
        else:
            self._ds_hold_run = 0
        if self._ds_hold_run > self._ds_hold_max:
            self._ds_hold_max = self._ds_hold_run
        if self._ds_hold_max >= self.done_hold_n - 1:
            self._ds_hold_hit = True

        # ---- deep: done_ok class switch ----
        if signals.get("cov_done_ok_valid"):
            cls = int(signals.get("cov_done_ok_class", 0) or 0)
            if self._ds_class_first is None:
                self._ds_class_first = cls
            elif cls != self._ds_class_first:
                self._ds_class_switch = True

        # ---- deep: frame word-count diversity (sampled on either adapter's
        # frame-completion pulse) ----
        if signals.get("cov_pk_mlast"):
            self._ds_word_set.add(int(signals.get("cov_pk_fwords", 0) or 0))
        if signals.get("cov_up_mlast"):
            self._ds_word_set.add(int(signals.get("cov_up_fwords", 0) or 0))
        if len(self._ds_word_set) >= 4:
            self._ds_word_hit = True

        if self._ds_hold_hit:
            self._hit("ds_hold_window_max", "hold_window_hit")
        if self._ds_class_switch:
            self._hit("ds_class_switch", "class_switch_hit")
        if self._ds_word_hit:
            self._hit("ds_word_diversity", "words_div_hit")

        # ---- sva/dataflow: busy streak ----
        if busy == 1:
            self._df_busy_run += 1
            if self._df_busy_run > self._df_busy_max:
                self._df_busy_max = self._df_busy_run
        else:
            self._df_busy_run = 0
        for b in (2, 4, 8):
            if self._df_busy_max >= b:
                self._hit("dataflow_busy_streak", "busy%d" % b)

        # ---- sva/dataflow: active dwell (cov_state != IDLE) ----
        if state != 0:
            self._df_active_run += 1
            if self._df_active_run > self._df_active_max:
                self._df_active_max = self._df_active_run
        else:
            self._df_active_run = 0
        for b in (1, 8, 16):
            if self._df_active_max >= b:
                self._hit("dataflow_active_dwell", "active%d" % b)

        # ---- sva/timing: hold dwell ----
        if hold == 1:
            self._tp_hold_run += 1
            if self._tp_hold_run > self._tp_hold_max:
                self._tp_hold_max = self._tp_hold_run
        else:
            self._tp_hold_run = 0
        if self._tp_hold_max >= 4:
            self._hit("timing_hold_dwell", "hold4")
        if self._tp_hold_max >= self.done_hold_n - 1:
            self._hit("timing_hold_dwell", "holdfull")

        # ---- sva/timing: idle dwell ----
        idle = (busy == 0 and hold == 0)
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
                pass  # cross-cycle trackers, advanced by _update_trackers
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
        # optional per-coverpoint valid gate (completion pulses)
        vflag = cp.get("valid_signal")
        if vflag and not signals.get(vflag, False):
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
            "coverage_pct": (self.hit_bins / self.total_bins * 100)
            if self.total_bins else 0,
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
