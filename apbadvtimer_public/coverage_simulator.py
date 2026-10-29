#!/usr/bin/env python3
"""
apbadvtimer_public - Coverage Simulator (VCS-equivalent, generic evaluator +
DUT-specific trackers).
Reads dut/coverage_meta.json and evaluates bins against a signals dict each
cycle, producing the same flat coverage vector the committee VCS covergroup
(dut/covergroup.svh) returns. Works unchanged on local_sim and Verilator
signal dictionaries (identical cov_* schema).

Generic part: basic / boundary / condition / temporal / cross / seq_hit bins
are evaluated straight from coverage_meta.json against the signals dict.
DUT-specific part: the deep (Q13-Q15) and sva trackers mirror the RTL trackers
in dut/covergroup.svh and the cover properties in dut/assert_cov.svh 1:1.
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
        # done_hold_n drives the parameter-keyed hold-window bins.
        self.done_hold_n = int(done_hold_n)
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
        # deep Q13: longest hold run >= done_hold_n - 1
        self._ds_hold_run = 0
        self._ds_hold_max = 0
        self._ds_hold_hit = False
        # deep Q14: two done_ok pulses with distinct classes
        self._ds_class_first = None
        self._ds_class_switch = False
        # deep Q15: >=3 distinct cov_cmp values at match cycles
        self._ds_cmp_set = set()
        self._ds_cmp_hit = False
        # sva: count streak (cov_en runs 2/4/8)
        self._sv_en_run = 0
        self._sv_en_max = 0
        # sva: active dwell (1/8/16)
        self._tp_act_run = 0
        self._tp_act_max = 0
        # sva: hold dwell (4 / done_hold_n-1)
        self._tp_hold_run = 0
        self._tp_hold_max = 0
        # sva: idle dwell (4/16)
        self._tp_idle_run = 0
        self._tp_idle_max = 0
        # sva: end restart (end_hit -> count step <=2)
        self._sv_end_arm = False
        self._sv_end_cnt = 0
        self._sv_end_hit = False
        self._sv_prev_cnt = 0
        # sva: match streak (cov_match level >=2 consecutive)
        self._sv_match_run = 0
        self._sv_match_max = 0

    def _update_trackers(self, signals: Dict):
        """Advance the cross-cycle trackers (mirrors covergroup.svh 1:1)."""
        en = int(signals.get("cov_en", 0) or 0)
        hold = int(signals.get("cov_hold", 0) or 0)
        idle = int(signals.get("cov_idle", 0) or 0)
        match = int(signals.get("cov_match", 0) or 0)
        end_hit = int(signals.get("cov_end_hit", 0) or 0)
        cnt = int(signals.get("cov_cnt", 0) or 0)
        done_valid = int(signals.get("cov_done_ok_valid", 0) or 0)
        done_class = int(signals.get("cov_done_ok_class", 0) or 0)
        cmp_val = int(signals.get("cov_cmp", 0) or 0)

        # ---- deep Q13: hold window length (parameter-driven) ----
        if hold == 1:
            self._ds_hold_run += 1
        else:
            self._ds_hold_run = 0
        if self._ds_hold_run > self._ds_hold_max:
            self._ds_hold_max = self._ds_hold_run
        if self._ds_hold_max >= self.done_hold_n - 1:
            self._ds_hold_hit = True

        # ---- deep Q14: done_ok class switch ----
        if done_valid:
            if self._ds_class_first is None:
                self._ds_class_first = done_class
            elif done_class != self._ds_class_first:
                self._ds_class_switch = True

        # ---- deep Q15: compare-value diversity at match cycles ----
        if match == 1:
            self._ds_cmp_set.add(cmp_val)
        if len(self._ds_cmp_set) >= 3:
            self._ds_cmp_hit = True

        if self._ds_hold_hit:
            self._hit("ds_hold_window_max", "hold_window_hit")
        if self._ds_class_switch:
            self._hit("ds_class_switch", "class_switch_hit")
        if self._ds_cmp_hit:
            self._hit("ds_cmp_diversity", "cmp_div_hit")

        # ---- sva: count streak (en run 2/4/8) ----
        if en == 1:
            self._sv_en_run += 1
            if self._sv_en_run > self._sv_en_max:
                self._sv_en_max = self._sv_en_run
        else:
            self._sv_en_run = 0
        for b in (2, 4, 8):
            if self._sv_en_max >= b:
                self._hit("count_streak", "count%d" % b)

        # ---- sva: active dwell (1/8/16) ----
        if en == 1:
            self._tp_act_run += 1
            if self._tp_act_run > self._tp_act_max:
                self._tp_act_max = self._tp_act_run
        else:
            self._tp_act_run = 0
        for b, name in ((1, "act1"), (8, "act8"), (16, "act16")):
            if self._tp_act_max >= b:
                self._hit("timing_active_dwell", name)

        # ---- sva: hold dwell ----
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

        # ---- sva: idle dwell ----
        if idle == 1:
            self._tp_idle_run += 1
            if self._tp_idle_run > self._tp_idle_max:
                self._tp_idle_max = self._tp_idle_run
        else:
            self._tp_idle_run = 0
        if self._tp_idle_max >= 4:
            self._hit("timing_idle_dwell", "idle4")
        if self._tp_idle_max >= 16:
            self._hit("timing_idle_dwell", "idle16")

        # ---- sva: end restart (end_hit -> count step <=2) ----
        step = 1 if cnt != self._sv_prev_cnt else 0
        self._sv_prev_cnt = cnt
        if end_hit == 1 and not self._sv_end_arm:
            self._sv_end_arm = True
            self._sv_end_cnt = 0
        elif self._sv_end_arm:
            if self._sv_end_cnt >= 2:
                self._sv_end_arm = False
            else:
                self._sv_end_cnt += 1
                if step:
                    self._sv_end_hit = True
                    self._sv_end_arm = False
        if self._sv_end_hit:
            self._hit("end_restart", "restart_hit")

        # ---- sva: match streak (match level >=2 consecutive) ----
        if match == 1:
            self._sv_match_run += 1
            if self._sv_match_run > self._sv_match_max:
                self._sv_match_max = self._sv_match_run
        else:
            self._sv_match_run = 0
        if self._sv_match_max >= 2:
            self._hit("match_streak", "match2")

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
    print(f"Total bins: {sim.total_bins}")
