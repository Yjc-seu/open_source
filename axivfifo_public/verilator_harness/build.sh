#!/bin/bash
# axivfifo_public - Verilator build (Linux/WSL).
# Builds axivfifo_top (+ upstream axi_vfifo / axi_vfifo_enc / axi_vfifo_dec /
# axi_vfifo_raw / axi_vfifo_raw_wr / axi_vfifo_raw_rd) and links sim_main.cpp
# to produce the runnable Vaxivfifo_top executable.
#
# The hidden configuration values LEN_OK_SET / DONE_HOLD_N are public
# Verilator module parameters baked in at BUILD time via -G. They are not
# exposed as runtime-assignable members, so sim_main.cpp only echoes them
# (argv) for verification.
#
# Defaults here are the PUBLIC PLACEHOLDERS (LEN_OK_SET=0 -> done_ok inert,
# DONE_HOLD_N=16) — identical out-of-box semantics to local_sim.py.
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
         -Wno-COMBDLY -Wno-DECLFILENAME -Wno-BLKANDNBLK -Wno-SELRANGE \
         -Wno-CMPCONST -Wno-VARHIDDEN -Wno-INITIALDLY -Wno-MULTIDRIVEN; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building axivfifo_public with Verilator ==="
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
    --top-module axivfifo_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/axivfifo_top.v" \
    "${DUT_DIR}/axi_vfifo.v" \
    "${DUT_DIR}/axi_vfifo_enc.v" \
    "${DUT_DIR}/axi_vfifo_dec.v" \
    "${DUT_DIR}/axi_vfifo_raw.v" \
    "${DUT_DIR}/axi_vfifo_raw_wr.v" \
    "${DUT_DIR}/axi_vfifo_raw_rd.v"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vaxivfifo_top.mk Vaxivfifo_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vaxivfifo_top"
