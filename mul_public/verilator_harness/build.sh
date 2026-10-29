#!/bin/bash
# mul_public - Verilator build + Python binding (Linux/WSL).
# Builds mul_top (+ upstream projf mul core) and links sim_main.cpp to
# produce the runnable Vmul_top executable.
#
# The hidden configuration values A_OK_SET / DONE_HOLD_N are public
# Verilator module parameters baked in at BUILD time via -G. They are not
# exposed as runtime-assignable members (Verilator >=5.020 has no such
# binding), so sim_main.cpp only echoes them (argv) for verification.
#
# Defaults here are the PUBLIC PLACEHOLDERS (A_OK_SET=0 -> done_ok inert,
# DONE_HOLD_N=16) — identical out-of-box semantics to local_sim.py.
# The eval-side truth is injected only by setting the environment variables
# before calling build.sh (internal verification); no secret is committed.

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DUT_DIR="${SCRIPT_DIR}/../dut"
OBJ_DIR="${SCRIPT_DIR}/obj_dir"

# Hidden config values; override via the environment when verifying.
# !!! Keep these as the public placeholders — never bake eval truth here.
A_OK_SET=${A_OK_SET:-0}
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
         -Wno-COMBDLY -Wno-DECLFILENAME -Wno-BLKANDNBLK -Wno-MULTIDRIVEN; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building mul_public with Verilator ==="
echo "  A_OK_SET=$A_OK_SET  DONE_HOLD_N=$DONE_HOLD_N"
echo "  warning flags:${WARN_FLAGS}"

${VERILATOR} \
    --cc \
    --exe \
    --public \
    --trace \
    ${WARN_FLAGS} \
    -GA_OK_SET="${A_OK_SET}" \
    -GDONE_HOLD_N="${DONE_HOLD_N}" \
    --top-module mul_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/mul_top.v" \
    "${DUT_DIR}/mul.sv"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vmul_top.mk Vmul_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vmul_top"
