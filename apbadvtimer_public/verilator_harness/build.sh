#!/bin/bash
# apbadvtimer_public - Verilator build + Python binding (Linux/WSL).
# Builds apbadvtimer_top (+ upstream adv_timer_apb_if / timer_module and
# sub-blocks / pulp_clock_gating) and links sim_main.cpp to produce the
# runnable Vapbadvtimer_top executable.
#
# The hidden configuration values CMP_OK_SET / DONE_HOLD_N are public
# Verilator module parameters baked in at BUILD time via -G. They are not
# exposed as runtime-assignable members, so sim_main.cpp only echoes them
# (argv) for verification.
#
# Defaults here are the PUBLIC PLACEHOLDERS (CMP_OK_SET=0 -> done_ok inert,
# DONE_HOLD_N=16) — identical out-of-box semantics to local_sim.py. The
# eval-side truth is injected only by setting the environment variables
# before calling build.sh (internal verification); no secret is committed.
#
# Note: upstream apb_adv_timer.sv (4-timer full top), lut_4x4.sv and
# out_filter.sv are shipped in dut/ for completeness but are not compiled:
# the wrapper selectively instantiates timer0 only (see dut_spec.md §1).

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DUT_DIR="${SCRIPT_DIR}/../dut"
OBJ_DIR="${SCRIPT_DIR}/obj_dir"

# Hidden config values; override via the environment when verifying.
# !!! Keep these as the public placeholders — never bake eval truth here.
CMP_OK_SET=${CMP_OK_SET:-0}
DONE_HOLD_N=${DONE_HOLD_N:-16}

# Clean previous build
rm -rf "${OBJ_DIR}"
mkdir -p "${OBJ_DIR}"

VERILATOR=${1:-verilator}

# Warning-suppression flags differ between Verilator releases (e.g. 4.0xx has
# no UNUSEDSIGNAL / UNUSEDPARAM / LATCH categories).  Probe each candidate once
# and keep only the ones this Verilator understands.
WARN_FLAGS=""
for f in -Wno-fatal -Wno-UNUSEDSIGNAL -Wno-UNUSEDPARAM -Wno-UNDRIVEN -Wno-UNUSED \
         -Wno-WIDTH -Wno-LATCH -Wno-UNOPTFLAT -Wno-CASEINCOMPLETE -Wno-CASEOVERLAP \
         -Wno-WIDTHTRUNC -Wno-WIDTHEXPAND -Wno-IMPLICIT -Wno-PINMISSING \
         -Wno-COMBDLY -Wno-DECLFILENAME -Wno-BLKANDNBLK -Wno-CLK_GATE \
         -Wno-MULTITOP -Wno-VARHIDDEN; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building apbadvtimer_public with Verilator ==="
echo "  CMP_OK_SET=$CMP_OK_SET  DONE_HOLD_N=$DONE_HOLD_N"
echo "  warning flags:${WARN_FLAGS}"

${VERILATOR} \
    --cc \
    --exe \
    --public \
    --trace \
    --Mdir "${OBJ_DIR}" \
    ${WARN_FLAGS} \
    -GCMP_OK_SET="${CMP_OK_SET}" \
    -GDONE_HOLD_N="${DONE_HOLD_N}" \
    --top-module apbadvtimer_top \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/apbadvtimer_top.v" \
    "${DUT_DIR}/adv_timer_apb_if.sv" \
    "${DUT_DIR}/timer_module.sv" \
    "${DUT_DIR}/timer_cntrl.sv" \
    "${DUT_DIR}/input_stage.sv" \
    "${DUT_DIR}/prescaler.sv" \
    "${DUT_DIR}/up_down_counter.sv" \
    "${DUT_DIR}/comparator.sv" \
    "${DUT_DIR}/pulp_clk_cells.sv"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vapbadvtimer_top.mk Vapbadvtimer_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vapbadvtimer_top"
