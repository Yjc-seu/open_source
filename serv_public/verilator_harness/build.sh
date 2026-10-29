#!/bin/bash
# serv_public - Verilator build + Python binding (Linux/WSL).
# Builds serv_top (+ upstream SERV rtl) and links sim_main.cpp to produce the
# runnable Vserv_top executable.
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
         -Wno-INITIALDLY -Wno-CASEINCOMPLETE -Wno-TIMESCALEMOD -Wno-LITENDIAN \
         -Wno-MULTIDRIVEN -Wno-VARHIDDEN; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building serv_public with Verilator ==="
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
    --top-module serv_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/serv_top.v" \
    "${DUT_DIR}/serv_rf_top.v" \
    "${DUT_DIR}/serv_top_upstream.v" \
    "${DUT_DIR}/serv_rf_ram_if.v" \
    "${DUT_DIR}/serv_rf_ram.v" \
    "${DUT_DIR}/serv_rf_if.v" \
    "${DUT_DIR}/serv_state.v" \
    "${DUT_DIR}/serv_decode.v" \
    "${DUT_DIR}/serv_immdec.v" \
    "${DUT_DIR}/serv_bufreg.v" \
    "${DUT_DIR}/serv_bufreg2.v" \
    "${DUT_DIR}/serv_ctrl.v" \
    "${DUT_DIR}/serv_alu.v" \
    "${DUT_DIR}/serv_mem_if.v" \
    "${DUT_DIR}/serv_csr.v"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vserv_top.mk Vserv_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vserv_top"
