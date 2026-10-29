#!/usr/bin/env python3
"""
darkriscv_public - Coverage Simulator (VCS-equivalent).
Per the interface contract, the canonical CoverageSimulator lives in
local_sim.py (alongside DarkriscvPublic); this module re-exports it so the
package layout matches the picorv32_public template (cross_check.py /
verify_all_bins.py import from here).
"""

from local_sim import CoverageSimulator  # noqa: F401

if __name__ == "__main__":
    import os
    here = os.path.dirname(os.path.abspath(__file__))
    sim = CoverageSimulator(os.path.join(here, "dut", "coverage_meta.json"))
    print(f"Total bins: {sim.total_bins}")
