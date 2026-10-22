#!/bin/bash
# aes_public - Verilator build + Python binding (Linux/WSL).
# Builds aes_top (+ upstream aes_core / aes_encipher_block / aes_decipher_block
# / aes_key_mem / aes_sbox / aes_inv_sbox) and links sim_main.cpp to produce
# the runnable Vaes_top executable.
#
# The hidden configuration values MODE_OK_SET / DONE_HOLD_N are public
# Verilator module parameters baked in at BUILD time via -G. They are not
# exposed as runtime-assignable members (Verilator >=5.020 has no such
# binding), so sim_main.cpp only echoes them (argv) for verification.
#
# Defaults here are the PUBLIC PLACEHOLDERS (MODE_OK_SET=0 -> done_ok inert,
# DONE_HOLD_N=16) — identical out-of-box semantics to local_sim.py.
# The eval-side truth is injected only by setting the environment variables
# before calling build.sh (internal verification); no secret is committed.

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DUT_DIR="${SCRIPT_DIR}/../dut"
OBJ_DIR="${SCRIPT_DIR}/obj_dir"

# Hidden config values; override via the environment when verifying.
# !!! Keep these as the public placeholders — never bake eval truth here.
MODE_OK_SET=${MODE_OK_SET:-0}
DONE_HOLD_N=${DONE_HOLD_N:-16}

# Clean previous build
rm -rf "${OBJ_DIR}"
mkdir -p "${OBJ_DIR}"

VERILATOR=${1:-verilator}

# Runtime parameter assignment (sim_main.cpp argv MODE_OK_SET / DONE_HOLD_N)
# only works on Verilator >= 5.020; enable the C++ flag there, otherwise rely
# on the -G baking below.
VER_MAJOR=$("${VERILATOR}" --version | awk '{print $2}' | cut -d. -f1 | tr -cd '0-9')
if [ -n "${VER_MAJOR}" ] && [ "${VER_MAJOR}" -ge 5 ]; then
    PARAM_CFLAGS='-CFLAGS -DVL_PARAM_RUNTIME_OK'
else
    PARAM_CFLAGS=""
fi

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

echo "=== Building aes_public with Verilator ==="
echo "  MODE_OK_SET=$MODE_OK_SET  DONE_HOLD_N=$DONE_HOLD_N"
echo "  warning flags:${WARN_FLAGS}"

${VERILATOR} \
    --cc \
    --exe \
    --public \
    --trace \
    ${PARAM_CFLAGS} \
    ${WARN_FLAGS} \
    -GMODE_OK_SET="${MODE_OK_SET}" \
    -GDONE_HOLD_N="${DONE_HOLD_N}" \
    --top-module aes_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/aes_top.v" \
    "${DUT_DIR}/aes_core.v" \
    "${DUT_DIR}/aes_encipher_block.v" \
    "${DUT_DIR}/aes_decipher_block.v" \
    "${DUT_DIR}/aes_key_mem.v" \
    "${DUT_DIR}/aes_sbox.v" \
    "${DUT_DIR}/aes_inv_sbox.v"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vaes_top.mk Vaes_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vaes_top"
