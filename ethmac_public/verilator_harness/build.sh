#!/bin/bash
# ethmac_public - Verilator build + Python binding (Linux/WSL).
# Builds ethmac_top (+ upstream eth_mac_1g / eth_mac_1g_rx / eth_mac_1g_tx /
# axis_async_frame_fifo / lfsr) and links sim_main.cpp to produce the runnable
# Vethmac_top executable.
#
# The hidden configuration values LEN_OK_SET / FRAME_HOLD_N are public
# Verilator module parameters baked in at BUILD time via -G. They are not
# exposed as runtime-assignable members on Verilator 4.0xx, so sim_main.cpp
# only echoes them (argv) for verification.
#
# Defaults here are the PUBLIC PLACEHOLDERS (LEN_OK_SET=0 -> frame_ok inert,
# FRAME_HOLD_N=16) — identical out-of-box semantics to local_sim.py. The
# eval-side truth is injected only by setting the environment variables
# before calling build.sh (internal verification); no secret is committed.

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DUT_DIR="${SCRIPT_DIR}/../dut"
OBJ_DIR="${SCRIPT_DIR}/obj_dir"

# Hidden config values; override via the environment when verifying.
# !!! Keep these as the public placeholders — never bake eval truth here.
LEN_OK_SET=${LEN_OK_SET:-0}
FRAME_HOLD_N=${FRAME_HOLD_N:-16}

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
         -Wno-UNUSEDPARAM; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building ethmac_public with Verilator ==="
echo "  LEN_OK_SET=$LEN_OK_SET  FRAME_HOLD_N=$FRAME_HOLD_N"
echo "  warning flags:${WARN_FLAGS}"

${VERILATOR} \
    --cc \
    --exe \
    --public \
    --trace \
    ${WARN_FLAGS} \
    -GLEN_OK_SET="${LEN_OK_SET}" \
    -GFRAME_HOLD_N="${FRAME_HOLD_N}" \
    --top-module ethmac_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/ethmac_top.v" \
    "${DUT_DIR}/eth_mac_1g.v" \
    "${DUT_DIR}/eth_mac_1g_rx.v" \
    "${DUT_DIR}/eth_mac_1g_tx.v" \
    "${DUT_DIR}/axis_async_frame_fifo.v" \
    "${DUT_DIR}/lfsr.v"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vethmac_top.mk Vethmac_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vethmac_top"
