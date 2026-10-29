#!/bin/bash
# sha512_public - Verilator build + Python binding (Linux/WSL).
# Builds sha512_top (+ upstream sha512_core / sha512_h_constants /
# sha512_k_constants / sha512_w_mem / sha512) and links sim_main.cpp to
# produce the runnable Vsha512_top executable.
#
# The hidden configuration values LEN_OK_SET / DONE_HOLD_N are public
# Verilator module parameters baked in at BUILD time via -G. They are not
# exposed as runtime-assignable members (Verilator >=5.020 has no such
# binding), so sim_main.cpp only echoes them (argv) for verification.
#
# Defaults here are the PUBLIC PLACEHOLDERS (LEN_OK_SET=0 -> done_ok
# inert, DONE_HOLD_N=16) — identical out-of-box semantics to local_sim.py.
# The eval-side truth is injected only by setting the environment variables
# before calling build.sh (internal verification); no secret is committed.

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DUT_DIR="${SCRIPT_DIR}/../dut"
OBJ_DIR="${SCRIPT_DIR}/obj_dir"

# Hidden config values; override via the environment when verifying.
# !!! Keep these as the public placeholders — never bake eval truth here.
LEN_OK_SET=${LEN_OK_SET:-0}
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
         -Wno-COMBDLY -Wno-DECLFILENAME -Wno-BLKANDNBLK; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building sha512_public with Verilator ==="
echo "  LEN_OK_SET=$LEN_OK_SET  DONE_HOLD_N=$DONE_HOLD_N"
echo "  warning flags:${WARN_FLAGS}"

${VERILATOR} \
    --cc \
    --exe \
    --public \
    --trace \
    ${WARN_FLAGS} \
    -GLEN_OK_SET="${LEN_OK_SET}" \
    -GDONE_HOLD_N="${DONE_HOLD_N}" \
    --top-module sha512_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/sha512_top.v" \
    "${DUT_DIR}/sha512_core.v" \
    "${DUT_DIR}/sha512_h_constants.v" \
    "${DUT_DIR}/sha512_k_constants.v" \
    "${DUT_DIR}/sha512_w_mem.v" \
    "${DUT_DIR}/sha512.v"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vsha512_top.mk Vsha512_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vsha512_top"
