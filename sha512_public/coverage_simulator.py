#!/usr/bin/env python3
"""
sha512_public - Coverage Simulator (VCS-equivalent, generic evaluator +
DUT-specific trackers).
Reads dut/coverage_meta.json and evaluates bins against a signals dict each
cycle, producing the same flat coverage vector the committee VCS covergroup
(dut/covergroup.svh) returns. Works unchanged on local_sim and Verilator
signal dictionaries (identical cov_* schema).

Generic part: basic / boundary / condition / temporal / cross / seq_hit bins
are evaluated straight from coverage_meta.json against the signals dict.
DUT-specific part: the deep (Q13-Q15) and sva trackers mirror the RTL trackers
in dut/covergroup.svh and the cover properties in dut/assert_cov.svh 1:1.
SHA-512 adaptations vs the sha256 sibling: the sustained next-chain window
is 90 cycles (single-block standard timing is 82 cycles) and the round-depth
bins are rd1/rd16/rd32 (80-round compression).
"""

import json
import os
from typing import Dict, List

import numpy as np

ST_IDLE, ST_BLOCKLOAD, ST_ROUNDS, ST_READY = 0, 1, 2, 3


class CoverageSimulator:
    def __init__(self, meta_path: str, done_hold_n: int = 16):
        with open(meta_path, "r", encoding="utf-8") as f:
            self.meta = json.load(f)
        self.coverpoints = self.meta["coverpoints"]
        # done_hold_n drives the parameter-keyed hold-window bins.
        self.done_hold_n = done_hold_n
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
        self._prev_dv = 0
        # deep Q13: longest hold run >= done_hold_n - 1
        self._ds_hold_run = 0
        self._ds_hold_max = 0
        self._ds_hold_hit = False
        # deep Q14: two done_ok pulses with distinct classes
        self._ds_class_first = None
        self._ds_class_switch = False
        # deep Q15: >=3 distinct len_low values across digest completions
        self._ds_len_set = set()
        self._ds_len_hit = False
        # sva: done restart (two digest completions)
        self._sva_dv_seen = False
        self._sva_restart = False
        # sva: blockload restart (two blockload windows)
        self._sva_load_windows = 0
        self._sva_prev_blockload = 0
        self._sva_load_restart = False
        # sva: multi hold windows
        self._sva_hold_windows = 0
        self._sva_prev_hold = 0
        self._sva_multi_hold = False
        # dataflow: busy streak
        self._df_busy_run = 0
        self._df_busy_max = 0
        # dataflow: consecutive digest completions (gap <= 90 cycles)
        self._df_next_gap = 0
        self._df_next_run = 0
        self._df_next_max = 0
        # timing: round progression depth
        self._tp_round_max = 0
        # timing: hold / idle dwell maxima
        self._tp_hold_run = 0
        self._tp_hold_max = 0
        self._tp_idle_run = 0
        self._tp_idle_max = 0

    def _update_trackers(self, signals: Dict):
        """Advance the cross-cycle trackers (mirrors covergroup.svh 1:1).

        Built purely from exported cov_* observation signals, so the same
        logic runs unchanged on both the local_sim and Verilator backends.
        """
        st = int(signals.get("cov_state", 0) or 0)
        hold = int(signals.get("cov_hold", 0) or 0)
        busy = int(signals.get("cov_busy", 0) or 0)
        dv = int(signals.get("cov_digest_valid", 0) or 0)
        rnd = int(signals.get("cov_round", 0) or 0)
        len_low = int(signals.get("cov_len_low", 0) or 0)
        dv_evt = bool(dv and not self._prev_dv)
        self._prev_dv = dv

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
        if signals.get("cov_done_ok_valid"):
            cls = int(signals.get("cov_done_ok_class", 0) or 0)
            if self._ds_class_first is None:
                self._ds_class_first = cls
            elif cls != self._ds_class_first:
                self._ds_class_switch = True

        # ---- deep Q15: len diversity across digest completions ----
        if dv_evt:
            self._ds_len_set.add(len_low)
        if len(self._ds_len_set) >= 3:
            self._ds_len_hit = True

        if self._ds_hold_hit:
            self._hit("ds_hold_window_max", "hold_window_hit")
        if self._ds_class_switch:
            self._hit("ds_done_class_switch", "class_switch_hit")
        if self._ds_len_hit:
            self._hit("ds_len_diversity", "len_div_hit")

        # ---- sva: done restart ----
        if dv_evt:
            if self._sva_dv_seen:
                self._sva_restart = True
            self._sva_dv_seen = True

        # ---- sva: blockload restart ----
        if st == ST_BLOCKLOAD and self._sva_prev_blockload == 0:
            self._sva_load_windows += 1
        self._sva_prev_blockload = 1 if st == ST_BLOCKLOAD else 0
        if self._sva_load_windows >= 2:
            self._sva_load_restart = True

        # ---- sva: multi hold windows ----
        if hold == 1 and self._sva_prev_hold == 0:
            self._sva_hold_windows += 1
        self._sva_prev_hold = hold
        if self._sva_hold_windows >= 2:
            self._sva_multi_hold = True

        if self._sva_restart:
            self._hit("assert_done_restart", "restart_hit")
        if self._sva_load_restart:
            self._hit("assert_load_restart", "load_restart_hit")
        if self._sva_multi_hold:
            self._hit("assert_multi_hold", "multi_hold_hit")

        # ---- dataflow: busy streak ----
        if busy == 1:
            self._df_busy_run += 1
            if self._df_busy_run > self._df_busy_max:
                self._df_busy_max = self._df_busy_run
        else:
            self._df_busy_run = 0
        for b in (2, 4, 8):
            if self._df_busy_max >= b:
                self._hit("dataflow_busy_streak", "busy%d" % b)

        # ---- dataflow: consecutive digest completions (chain) ----
        # SHA-512 single-block timing: acceptance + 80 rounds + 1 DONE =
        # 82 cycles, so a preloaded back-to-back chain completes every
        # ~83 cycles; the sustained-chain window is 90 cycles.
        if dv_evt:
            self._df_next_run = (self._df_next_run + 1
                                 if self._df_next_gap <= 90 else 1)
            self._df_next_gap = 0
        else:
            self._df_next_gap += 1
        if self._df_next_run > self._df_next_max:
            self._df_next_max = self._df_next_run
        if self._df_next_max >= 2:
            self._hit("dataflow_next_chain", "next2")
        if self._df_next_max >= 4:
            self._hit("dataflow_next_chain", "next4")

        # ---- timing: round progression depth (80-round compression) ----
        if rnd > self._tp_round_max:
            self._tp_round_max = rnd
        for b, name in ((1, "rd1"), (16, "rd16"), (32, "rd32")):
            if self._tp_round_max >= b:
                self._hit("timing_round_dwell", name)

        # ---- timing: hold dwell ----
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

        # ---- timing: idle dwell (IDLE state, no hold, no busy) ----
        idle = (st == ST_IDLE and hold == 0 and busy == 0)
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
        # normalize for comparison
        if isinstance(val, bool):
            val = 1 if val else 0
        val = int(val)
        if cp["type"] == "temporal":
            # requires the valid flag in the same cycle
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
