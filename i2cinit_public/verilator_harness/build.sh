#!/bin/bash
# i2cinit_public - Verilator build + Python binding (Linux/WSL).
# Builds i2cinit_top (+ i2c_init + i2c_master) and links sim_main.cpp to
# produce the runnable Vi2cinit_top executable.
#
# The hidden configuration values CFG_OK_SET / DONE_HOLD_N are module
# parameters of i2cinit_top.  They are baked in at BUILD time via -G with the
# PUBLIC PLACEHOLDERS (0 / 16) by default; the eval-side truth is injected
# only by setting the environment variables before calling build.sh (internal
# verification).  No secret is committed.
#
# sim_main.cpp additionally reads CFG_OK_SET / DONE_HOLD_N from argv for
# Verilator >= 5.020, which supports runtime assignment of
# /* verilator public */ parameters; on older Verilator versions remove the
# two runtime assignments in sim_main.cpp and rely on the -G baking below.

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DUT_DIR="${SCRIPT_DIR}/../dut"
OBJ_DIR="${SCRIPT_DIR}/obj_dir"

# Hidden config values; override via the environment when verifying.
# !!! Keep these as the public placeholders — never bake eval truth here.
CFG_OK_SET=${CFG_OK_SET:-0}
DONE_HOLD_N=${DONE_HOLD_N:-16}

# Clean previous build
rm -rf "${OBJ_DIR}"
mkdir -p "${OBJ_DIR}"

VERILATOR=${1:-verilator}

# Runtime parameter assignment (sim_main.cpp argv CFG_OK_SET / DONE_HOLD_N)
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
         -Wno-COMBDLY -Wno-DECLFILENAME; do
    if ${VERILATOR} ${f} --version >/dev/null 2>&1; then
        WARN_FLAGS="${WARN_FLAGS} ${f}"
    fi
done

echo "=== Building i2cinit_public with Verilator ==="
echo "  CFG_OK_SET=$CFG_OK_SET  DONE_HOLD_N=$DONE_HOLD_N"
echo "  warning flags:${WARN_FLAGS}"

${VERILATOR} \
    --cc \
    --exe \
    --public \
    --trace \
    ${WARN_FLAGS} \
    ${PARAM_CFLAGS} \
    -GCFG_OK_SET="${CFG_OK_SET}" \
    -GDONE_HOLD_N="${DONE_HOLD_N}" \
    --top-module i2cinit_top \
    -Mdir "${OBJ_DIR}" \
    "${SCRIPT_DIR}/sim_main.cpp" \
    "${DUT_DIR}/i2cinit_top.v" \
    "${DUT_DIR}/i2c_init.v" \
    "${DUT_DIR}/i2c_master.v"

echo "=== Building Verilator library ==="
cd "${OBJ_DIR}"
make -j$(nproc) -f Vi2cinit_top.mk Vi2cinit_top

echo "=== Build complete ==="
echo "Executable: ${OBJ_DIR}/Vi2cinit_top"
