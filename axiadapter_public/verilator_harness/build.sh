#!/bin/bash
# axiadapter_public - Verilator build (Linux/WSL).
# Builds axiadapter_top (+ upstream axi_adapter / axi_adapter_rd /
# axi_adapter_wr) and links sim_main.cpp to produce the runnable
# Vaxiadapter_top executable.
#
# The hidden configuration values ADDR_OK_SET / DONE_HOLD_N are public
# Verilator module parameters baked in at BUILD time via -G. They are not
# exposed as runtime-assignable members, so sim_main.cpp only echoes them
# (argv) for verification.
#
# Defaults here are the PUBLIC PLACEHOLDERS (ADDR_OK_SET=0 -> done_ok inert,
# DONE_HOLD_N=16) — identical out-of-box semantics to local_sim.py.
# The eval-side truth is injected only by setting the environment variables
# before calling build.sh (internal verification); no secret is committed.

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DUT_DIR="${SCRIPT_DIR}/../dut"
OBJ_DIR="${SCRIPT_DIR}/obj_dir"

# Hidden config values; override via the environment when verifying.
# !!! Keep these as the public placeholders — never bake eval truth here.
ADDR_OK_SET=${ADDR_OK_SET:-0}
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
         -Wno-CMPCONST -Wno-VARHIDDEN -Wno-INITIALDLY -Wno-TIMESCALEMOD \
         -Wno-MULTIDRIVEN -Wno-STMTDLY; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building axiadapter_public with Verilator ==="
echo "  ADDR_OK_SET=$ADDR_OK_SET  DONE_HOLD_N=$DONE_HOLD_N"
echo "  warning flags:${WARN_FLAGS}"

${VERILATOR} \
    --cc \
    --exe \
    --public \
    --trace \
    ${WARN_FLAGS} \
    -GADDR_OK_SET="${ADDR_OK_SET}" \
    -GDONE_HOLD_N="${DONE_HOLD_N}" \
    --top-module axiadapter_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/axiadapter_top.v" \
    "${DUT_DIR}/axi_adapter.v" \
    "${DUT_DIR}/axi_adapter_rd.v" \
    "${DUT_DIR}/axi_adapter_wr.v"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vaxiadapter_top.mk Vaxiadapter_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vaxiadapter_top"
