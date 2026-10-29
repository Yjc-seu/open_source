#!/bin/bash
# femtorv_public - Verilator build + Python binding (Linux/WSL).
# Builds femtorv_top (+ upstream femtorv32_quark) and links sim_main.cpp to
# produce the runnable Vfemtorv_top executable.
#
# The hidden configuration values OP_OK_SET / TRAP_HOLD_N are public Verilator
# module parameters baked in at BUILD time via -G. They are not exposed as
# runtime-assignable members (Verilator >=5.020 has no such binding), so
# sim_main.cpp only echoes them (argv) for verification.
#
# Defaults here are the PUBLIC PLACEHOLDERS (OP_OK_SET=0 -> done_ok inert,
# TRAP_HOLD_N=16) — identical out-of-box semantics to local_sim.py. The
# eval-side truth is injected only by setting the environment variables before
# calling build.sh (internal verification); no secret is committed.

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DUT_DIR="${SCRIPT_DIR}/../dut"
OBJ_DIR="${SCRIPT_DIR}/obj_dir"

# Hidden config values; override via the environment when verifying.
# !!! Keep these as the public placeholders — never bake eval truth here.
OP_OK_SET=${OP_OK_SET:-0}
TRAP_HOLD_N=${TRAP_HOLD_N:-16}

# Clean previous build
rm -rf "${OBJ_DIR}"
mkdir -p "${OBJ_DIR}"

VERILATOR=${1:-verilator}

# Warning-suppression flags differ between Verilator releases (e.g. 4.0xx has
# no UNUSEDSIGNAL / UNUSEDPARAM / LATCH categories). Probe each candidate once
# and keep only the ones this Verilator understands.
WARN_FLAGS=""
for f in -Wno-fatal -Wno-UNUSEDSIGNAL -Wno-UNUSEDPARAM -Wno-UNDRIVEN -Wno-UNUSED \
         -Wno-WIDTH -Wno-LATCH -Wno-UNOPTFLAT -Wno-CASEINCOMPLETE -Wno-CASEOVERLAP \
         -Wno-WIDTHTRUNC -Wno-WIDTHEXPAND -Wno-IMPLICIT -Wno-PINMISSING \
         -Wno-COMBDLY -Wno-DECLFILENAME -Wno-BLKANDNBLK -Wno-INFINITELOOP \
         -Wno-INITIALDLY -Wno-CASEINCOMPLETE -Wno-TIMESCALEMOD -Wno-LITENDIAN; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building femtorv_public with Verilator ==="
echo "  OP_OK_SET=$OP_OK_SET  TRAP_HOLD_N=$TRAP_HOLD_N"
echo "  warning flags:${WARN_FLAGS}"

${VERILATOR} \
    --cc \
    --exe \
    --public \
    --trace \
    ${WARN_FLAGS} \
    -GOP_OK_SET="${OP_OK_SET}" \
    -GTRAP_HOLD_N="${TRAP_HOLD_N}" \
    --top-module femtorv_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/femtorv_top.v" \
    "${DUT_DIR}/femtorv32_quark.v"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vfemtorv_top.mk Vfemtorv_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vfemtorv_top"
