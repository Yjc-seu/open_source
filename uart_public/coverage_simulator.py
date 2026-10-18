#!/usr/bin/env python3
"""
uart_public - Coverage Simulator (VCS-equivalent, generic evaluator +
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

TX_STOP = 3
TX_IDLE = 0
RX_STOP = 3


class CoverageSimulator:
    def __init__(self, meta_path: str, baud_hold_n: int = 16):
        with open(meta_path, "r", encoding="utf-8") as f:
            self.meta = json.load(f)
        self.coverpoints = self.meta["coverpoints"]
        # baud_hold_n drives the parameter-keyed hold-window bins.
        self.baud_hold_n = baud_hold_n
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
        # prev-state (registered-edge event detection)
        self._prev_tx_state = TX_IDLE
        self._prev_rx_state = TX_IDLE  # TX_IDLE == RX_IDLE == 0
        # deep Q13: longest hold run >= baud_hold_n - 1
        self._ds_hold_run = 0
        self._ds_hold_max = 0
        self._ds_hold_hit = False
        # deep Q14: two baud_ok pulses with distinct classes
        self._ds_class_first = None
        self._ds_class_switch = False
        # deep Q15: >=3 distinct prescale values across tx completions
        self._ds_prescale_set = set()
        self._ds_prescale_hit = False
        # sva: bidi busy (both cores active, external mode)
        self._sva_bidi = False
        # sva: done then restart
        self._sva_done_seen = False
        self._sva_restart = False
        # sva: multi hold windows
        self._sva_hold_windows = 0
        self._sva_prev_hold = 0
        self._sva_multi_hold = False
        # dataflow: busy streak
        self._df_busy_run = 0
        self._df_busy_max = 0
        # dataflow: consecutive same-direction completions
        self._df_tx_run = 0
        self._df_rx_run = 0
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
        tx_st = int(signals.get("cov_tx_state", 0) or 0)
        rx_st = int(signals.get("cov_rx_state", 0) or 0)
        tx_done = (self._prev_tx_state == TX_STOP) and (tx_st == TX_IDLE)
        rx_done = (self._prev_rx_state == RX_STOP) and (rx_st != RX_STOP)
        self._prev_tx_state = tx_st
        self._prev_rx_state = rx_st

        hold = int(signals.get("cov_hold", 0) or 0)
        busy = int(signals.get("cov_busy", 0) or 0)
        pending = int(signals.get("cov_pending", 0) or 0)
        lb = int(signals.get("cov_loopback", 0) or 0)

        # ---- deep Q13: hold window length (parameter-driven) ----
        if hold == 1:
            self._ds_hold_run += 1
        else:
            self._ds_hold_run = 0
        if self._ds_hold_run > self._ds_hold_max:
            self._ds_hold_max = self._ds_hold_run
        if self._ds_hold_max >= self.baud_hold_n - 1:
            self._ds_hold_hit = True

        # ---- deep Q14: baud_ok class switch ----
        if signals.get("cov_baud_ok_valid"):
            cls = int(signals.get("cov_baud_ok_class", 0) or 0)
            if self._ds_class_first is None:
                self._ds_class_first = cls
            elif cls != self._ds_class_first:
                self._ds_class_switch = True

        # ---- deep Q15: prescale diversity across tx completions ----
        if tx_done:
            self._ds_prescale_set.add(int(signals.get("cov_prescale", 0) or 0))
        if len(self._ds_prescale_set) >= 3:
            self._ds_prescale_hit = True

        if self._ds_hold_hit:
            self._hit("ds_hold_window_max", "hold_window_hit")
        if self._ds_class_switch:
            self._hit("ds_baud_class_switch", "class_switch_hit")
        if self._ds_prescale_hit:
            self._hit("ds_prescale_diversity", "prescale_div_hit")

        # ---- sva: bidi busy ----
        if tx_st != TX_IDLE and rx_st != TX_IDLE and lb == 0:
            self._sva_bidi = True

        # ---- sva: done then restart ----
        if tx_done:
            if self._sva_done_seen:
                self._sva_restart = True
            self._sva_done_seen = True

        # ---- sva: multi hold windows ----
        if hold == 1 and self._sva_prev_hold == 0:
            self._sva_hold_windows += 1
        self._sva_prev_hold = hold
        if self._sva_hold_windows >= 2:
            self._sva_multi_hold = True

        if self._sva_bidi:
            self._hit("assert_bidi_busy", "bidi_hit")
        if self._sva_restart:
            self._hit("assert_done_restart", "restart_hit")
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

        # ---- dataflow: consecutive same-direction completions ----
        if tx_done:
            self._df_tx_run += 1
            self._df_rx_run = 0
        if rx_done:
            self._df_rx_run += 1
            self._df_tx_run = 0
        if self._df_tx_run >= 2:
            self._hit("dataflow_tx_run", "tx_run2")
        if self._df_tx_run >= 4:
            self._hit("dataflow_tx_run", "tx_run4")
        if self._df_rx_run >= 2:
            self._hit("dataflow_rx_run", "rx_run2")
        if self._df_rx_run >= 4:
            self._hit("dataflow_rx_run", "rx_run4")

        # ---- timing: active (busy) dwell ----
        if busy == 1:
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
        if self._tp_hold_max >= self.baud_hold_n - 1:
            self._hit("timing_hold_dwell", "holdfull")

        # ---- timing: idle dwell (no busy, no hold, no pending) ----
        idle = (busy == 0 and hold == 0 and pending == 0)
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
            vflag = cp.get("valid_signal", "cov_baud_ok_valid")
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
        # For crosses that involve the baud_ok class, the class is only valid
        # on the baud_ok pulse cycle.
        if "cov_baud_ok_class" in parents:
            if not signals.get("cov_baud_ok_valid", False):
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
