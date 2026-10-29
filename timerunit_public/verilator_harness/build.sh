#!/bin/bash
# timerunit_public - Verilator build + text-protocol executable (Linux/WSL).
# Builds timerunit_top (+ 4 upstream apb_timer_unit cores + counters) and
# links sim_main.cpp to produce the runnable Vtimerunit_top executable.
#
# The hidden configuration values CMP_OK_SET / DONE_HOLD_N are public
# Verilator module parameters baked in at BUILD time via -G. They are not
# exposed as runtime-assignable members, so sim_main.cpp only echoes them
# (argv) for verification.
#
# Defaults here are the PUBLIC PLACEHOLDERS (CMP_OK_SET=0 -> done_ok inert,
# DONE_HOLD_N=16) — identical out-of-box semantics to local_sim.py.
# The eval-side truth is injected only by setting the environment variables
# before calling build.sh (internal verification); no secret is committed.

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
         -Wno-COMBDLY -Wno-DECLFILENAME -Wno-BLKANDNBLK -Wno-LITENDIAN \
         -Wno-SELRANGE -Wno-INITIALDLY; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building timerunit_public with Verilator ==="
echo "  CMP_OK_SET=$CMP_OK_SET  DONE_HOLD_N=$DONE_HOLD_N"
echo "  warning flags:${WARN_FLAGS}"

${VERILATOR} \
    --cc \
    --exe \
    --public \
    --trace \
    ${WARN_FLAGS} \
    -GCMP_OK_SET="${CMP_OK_SET}" \
    -GDONE_HOLD_N="${DONE_HOLD_N}" \
    --top-module timerunit_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/timerunit_top.v" \
    "${DUT_DIR}/apb_timer_unit.sv" \
    "${DUT_DIR}/timer_unit_counter.sv" \
    "${DUT_DIR}/timer_unit_counter_presc.sv"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vtimerunit_top.mk Vtimerunit_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vtimerunit_top"
