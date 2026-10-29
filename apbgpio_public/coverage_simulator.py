#!/usr/bin/env python3
"""
apbgpio_public - Coverage Simulator (VCS-equivalent, generic evaluator +
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
        # deep Q13: longest hold run >= done_hold_n - 1
        self._ds_hold_run = 0
        self._ds_hold_max = 0
        self._ds_hold_hit = False
        # deep Q14: two done_ok pulses with distinct classes
        self._ds_class_first = None
        self._ds_class_switch = False
        # deep Q15: >=3 distinct OUT low-byte values across accepted writes
        self._ds_out_set = set()
        self._ds_out_hit = False
        # sva: multi hold windows
        self._sva_hold_windows = 0
        self._sva_prev_hold = 0
        self._sva_multi_hold = False
        # sva: done then restart (two done_ok pulses)
        self._sva_done_seen = False
        self._sva_restart = False
        # sva: int lifecycle (set pulse then clear pulse)
        self._sva_set_seen = False
        self._sva_int_cycle = False
        # sva: >=8 distinct accepted addresses
        self._sva_addr_set = set()
        self._sva_addr_div = False
        # dataflow: accepted-write streak
        self._df_wr_run = 0
        self._df_wr_max = 0
        # timing_param: dwell maxima
        self._tp_act_run = 0
        self._tp_act_max = 0
        self._tp_hold_run = 0
        self._tp_hold_max = 0
        self._tp_idle_run = 0
        self._tp_idle_max = 0

    def _update_trackers(self, signals: Dict):
        """Advance the cross-cycle trackers (mirrors covergroup.svh 1:1).

        Built purely from exported cov_* observation signals, so the same
        logic runs unchanged on both the local_sim and Verilator backends.
        """
        hold = int(signals.get("cov_hold", 0) or 0)
        wr_ok = int(signals.get("cov_wr_ok", 0) or 0)
        addr = int(signals.get("cov_addr", 0) or 0)
        dvalid = int(signals.get("cov_done_ok_valid", 0) or 0)
        int_set = int(signals.get("cov_int_set", 0) or 0)
        int_clr = int(signals.get("cov_int_clr", 0) or 0)
        status = int(signals.get("cov_int_status", 0) or 0)
        out = int(signals.get("cov_out", 0) or 0)

        # ---- deep Q13: hold window length (parameter-driven) ----
        if hold == 1:
            self._ds_hold_run += 1
        else:
            self._ds_hold_run = 0
        if self._ds_hold_run > self._ds_hold_max:
            self._ds_hold_max = self._ds_hold_run
        if self._ds_hold_max >= max(0, self.done_hold_n - 1):
            self._ds_hold_hit = True

        # ---- deep Q14: done_ok class switch ----
        if dvalid:
            cls = int(signals.get("cov_done_ok_class", 0) or 0)
            if self._ds_class_first is None:
                self._ds_class_first = cls
            elif cls != self._ds_class_first:
                self._ds_class_switch = True

        # ---- deep Q15: out low-byte diversity across accepted PADOUT writes
        if wr_ok and addr == 3:
            self._ds_out_set.add(out & 0xFF)
        if len(self._ds_out_set) >= 3:
            self._ds_out_hit = True

        if self._ds_hold_hit:
            self._hit("ds_hold_window_max", "hold_window_hit")
        if self._ds_class_switch:
            self._hit("ds_class_switch", "class_switch_hit")
        if self._ds_out_hit:
            self._hit("ds_out_diversity", "out_div_hit")

        # ---- sva: multi hold windows ----
        if hold == 1 and self._sva_prev_hold == 0:
            self._sva_hold_windows += 1
        self._sva_prev_hold = hold
        if self._sva_hold_windows >= 2:
            self._sva_multi_hold = True

        # ---- sva: done then restart ----
        if dvalid:
            if self._sva_done_seen:
                self._sva_restart = True
            self._sva_done_seen = True

        # ---- sva: int lifecycle ----
        if int_set:
            self._sva_set_seen = True
        if self._sva_set_seen and int_clr:
            self._sva_int_cycle = True

        # ---- sva: >=8 distinct accepted addresses ----
        if wr_ok:
            self._sva_addr_set.add(addr & 0x1F)
        if len(self._sva_addr_set) >= 8:
            self._sva_addr_div = True

        if self._sva_multi_hold:
            self._hit("assert_multi_hold", "multi_hold_hit")
        if self._sva_restart:
            self._hit("assert_done_restart", "restart_hit")
        if self._sva_int_cycle:
            self._hit("assert_int_lifecycle", "int_cycle_hit")
        if self._sva_addr_div:
            self._hit("assert_addr_diversity", "addr_div_hit")

        # ---- dataflow: accepted-write streak (read-clears excluded) ----
        if wr_ok and addr not in (9, 23):
            self._df_wr_run += 1
            if self._df_wr_run > self._df_wr_max:
                self._df_wr_max = self._df_wr_run
        else:
            self._df_wr_run = 0
        for b in (2, 4, 8):
            if self._df_wr_max >= b:
                self._hit("dataflow_wr_streak", "wr%d" % b)

        # ---- timing: active dwell (wr_ok | hold | done_ok) ----
        active = (wr_ok == 1 or hold == 1 or dvalid == 1)
        if active:
            self._tp_act_run += 1
            if self._tp_act_run > self._tp_act_max:
                self._tp_act_max = self._tp_act_run
        else:
            self._tp_act_run = 0
        for b, name in ((1, "act1"), (8, "act8"), (16, "act16")):
            if self._tp_act_max >= b:
                self._hit("timing_active_dwell", name)

        # ---- timing: hold dwell ----
        if hold == 1:
            self._tp_hold_run += 1
            if self._tp_hold_run > self._tp_hold_max:
                self._tp_hold_max = self._tp_hold_run
        else:
            self._tp_hold_run = 0
        if self._tp_hold_max >= 4:
            self._hit("timing_hold_dwell", "hold4")
        if self._tp_hold_max >= max(0, self.done_hold_n - 1):
            self._hit("timing_hold_dwell", "holdfull")

        # ---- timing: idle dwell (no access / no hold / no done / no int) ----
        idle = (wr_ok == 0 and hold == 0 and dvalid == 0 and status == 0)
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
    print(f"Total bins: {sim.total_bins}")
