#!/usr/bin/env bash
set -euo pipefail

# Generate game-derived AOT locally. No game executable or generated C++ is
# written to Git. Inputs must come from the user's own legally obtained dump.
: "${PSP_RECOMP:=psp_recomp}"
: "${GE2_GAME_DIR:=game}"

mkdir -p generated generated-modules/layout generated-modules/field

"${PSP_RECOMP}" "${GE2_GAME_DIR}/EBOOT.BIN" \
  --auto generated 0x08804000 0x4000

"${PSP_RECOMP}" "${GE2_GAME_DIR}/layout.bin" \
  --auto generated-modules/layout 0x08C00000 0x4000 --prefix ge2_layout

# Supply the offline A0-converted Field PRX as god_g000_Field_a0.prx.
"${PSP_RECOMP}" "${GE2_GAME_DIR}/god_g000_Field_a0.prx" \
  --auto generated-modules/field 0x08E00000 0x4000 --prefix ge2_field

echo "AOT generation finished. These module bases are provisional; do not link"
echo "module corpora until runtime module load addresses and registration are verified."
