#!/bin/bash
# axidma_public - Verilator build + Python binding (Linux/WSL).
# Builds axidma_top (+ upstream axi_dma / axi_dma_rd / axi_dma_wr) and links
# sim_main.cpp to produce the runnable Vaxidma_top executable.
#
# The hidden configuration values LEN_OK_SET / DONE_HOLD_N are public
# Verilator module parameters baked in at BUILD time via -G. They are not
# exposed as runtime-assignable members, so sim_main.cpp only echoes them
# (argv) for verification.
#
# Verilator 4.038 hard constraint (measured on this machine): -G values are
# baked at build time; the literal "0x0" is mis-parsed and decimal > 2^30 is
# corrupted on some 4.038 revisions, so zero is passed as "0" and non-zero
# values in 0x hex form (see the LEN_OK_SET_G / DONE_HOLD_N_G conversion).
#
# Defaults here are the PUBLIC PLACEHOLDERS (LEN_OK_SET=0 -> hold/done_ok
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

# Verilator 4.038 -G quirk (measured): the literal "0x0" is mis-parsed
# ("Mixing X/Z/? with digits not legal in decimal constant"), and decimal
# values > 2^30 are corrupted on some 4.038 revisions. Safe form per value:
# zero -> "0", non-zero -> hex "0x...". Both baked values use this form.
if [ "$LEN_OK_SET" = "0" ]; then
    LEN_OK_SET_G="0"
else
    LEN_OK_SET_G=$(printf '0x%X' "$LEN_OK_SET")
fi
if [ "$DONE_HOLD_N" = "0" ]; then
    DONE_HOLD_N_G="0"
else
    DONE_HOLD_N_G=$(printf '0x%X' "$DONE_HOLD_N")
fi

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
         -Wno-COMBDLY -Wno-DECLFILENAME -Wno-BLKANDNBLK -Wno-INITIALDLY \
         -Wno-MULTIDRIVEN -Wno-VARHIDDEN -Wno-PROCADD -Wno-INITIALDLY; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building axidma_public with Verilator ==="
echo "  LEN_OK_SET=$LEN_OK_SET (-G $LEN_OK_SET_G)  DONE_HOLD_N=$DONE_HOLD_N (-G $DONE_HOLD_N_G)"
echo "  warning flags:${WARN_FLAGS}"

${VERILATOR} \
    --cc \
    --exe \
    --public \
    --trace \
    ${WARN_FLAGS} \
    -GLEN_OK_SET="${LEN_OK_SET_G}" \
    -GDONE_HOLD_N="${DONE_HOLD_N_G}" \
    --top-module axidma_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/axidma_top.v" \
    "${DUT_DIR}/axi_dma.v" \
    "${DUT_DIR}/axi_dma_rd.v" \
    "${DUT_DIR}/axi_dma_wr.v"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vaxidma_top.mk Vaxidma_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vaxidma_top"
