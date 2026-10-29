#!/bin/bash
# projfuart_public - Verilator build + Python binding (Linux/WSL).
# Builds projfuart_top (+ upstream Project F uart_tx / uart_rx / uart_baud)
# and links sim_main.cpp to produce the runnable Vprojfuart_top executable.
#
# The hidden configuration values DIV_OK_SET / DONE_HOLD_N are public
# Verilator module parameters baked in at BUILD time via -G. They are not
# exposed as runtime-assignable members (Verilator 4.038 exposes ports, not
# top parameters, and >=5.020 has no parameter binding at all), so
# sim_main.cpp only echoes them (argv) for verification.
#
# The runtime div input (div[7:0] pin) is NOT a module parameter: it is a
# plain input port driven per cycle through the text protocol. div=0 selects
# the upstream uart_baud fixed-reference strobes (instanced here, CNT_INC
# default 25770 = 100 MHz -> 16x9600); div>=1 selects the wrapper's runtime
# accumulator (identical to uart_baud with CNT_INC = div<<16).
#
# Defaults here are the PUBLIC PLACEHOLDERS (DIV_OK_SET=0 -> done_ok inert,
# DONE_HOLD_N=16) — identical out-of-box semantics to local_sim.py.
# The eval-side truth is injected only by setting the environment variables
# before calling build.sh (internal verification); no secret is committed.

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DUT_DIR="${SCRIPT_DIR}/../dut"
OBJ_DIR="${SCRIPT_DIR}/obj_dir"

# Hidden config values; override via the environment when verifying.
# !!! Keep these as the public placeholders — never bake eval truth here.
DIV_OK_SET=${DIV_OK_SET:-0}
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

echo "=== Building projfuart_public with Verilator ==="
echo "  DIV_OK_SET=$DIV_OK_SET  DONE_HOLD_N=$DONE_HOLD_N"
echo "  warning flags:${WARN_FLAGS}"

${VERILATOR} \
    --cc \
    --exe \
    --public \
    --trace \
    ${WARN_FLAGS} \
    -GDIV_OK_SET="${DIV_OK_SET}" \
    -GDONE_HOLD_N="${DONE_HOLD_N}" \
    --top-module projfuart_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/projfuart_top.v" \
    "${DUT_DIR}/uart_rx.sv" \
    "${DUT_DIR}/uart_tx.sv" \
    "${DUT_DIR}/uart_baud.sv"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vprojfuart_top.mk Vprojfuart_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vprojfuart_top"
