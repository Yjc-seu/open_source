#!/bin/bash
# ethmacmii_public - Verilator build (Linux/WSL).
# Builds ethmacmii_top (+ upstream eth_mac_mii / mii_phy_if / eth_mac_1g /
# axis_gmii_rx / axis_gmii_tx / lfsr / ssio_sdr_in) and links sim_main.cpp to
# produce the runnable Vethmacmii_top executable.
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
# -Wno-TIMESCALEMOD: Verilator 4.038's TIMESCALEMOD check false-positives on
# the upstream files' `resetall + string-parameter generate branches (e.g.
# mii_phy_if / ssio_sdr_in XILINX-only branches report "timescale missing"
# although each file carries `timescale 1ns/1ps).
WARN_FLAGS=""
for f in -Wno-fatal -Wno-UNUSEDSIGNAL -Wno-UNUSEDPARAM -Wno-UNDRIVEN -Wno-UNUSED \
         -Wno-WIDTH -Wno-LATCH -Wno-UNOPTFLAT -Wno-CASEINCOMPLETE -Wno-CASEOVERLAP \
         -Wno-WIDTHTRUNC -Wno-WIDTHEXPAND -Wno-IMPLICIT -Wno-PINMISSING \
         -Wno-COMBDLY -Wno-DECLFILENAME -Wno-BLKANDNBLK -Wno-INITIALDLY \
         -Wno-UNUSEDPARAM -Wno-TIMESCALEMOD; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building ethmacmii_public with Verilator ==="
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
    --top-module ethmacmii_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/ethmacmii_top.v" \
    "${DUT_DIR}/eth_mac_mii.v" \
    "${DUT_DIR}/mii_phy_if.v" \
    "${DUT_DIR}/eth_mac_1g.v" \
    "${DUT_DIR}/axis_gmii_rx.v" \
    "${DUT_DIR}/axis_gmii_tx.v" \
    "${DUT_DIR}/lfsr.v" \
    "${DUT_DIR}/ssio_sdr_in.v"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vethmacmii_top.mk Vethmacmii_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vethmacmii_top"
