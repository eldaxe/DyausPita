#!/usr/bin/env bash
set -euo pipefail

# Generate each executable into its own corpus directory. Generated C++ and
# all game executables are local-only and must never be committed.
: "${PSP_RECOMP:=psp_recomp}"
: "${GE2_GAME_DIR:=game}"

mkdir -p generated generated-modules/layout generated-modules/field

"${PSP_RECOMP}" "${GE2_GAME_DIR}/EBOOT.BIN" \
  --auto generated 0x08804000 0x4000

"${PSP_RECOMP}" "${GE2_GAME_DIR}/layout.bin" \
  --auto generated-modules/layout 0x08C00000 0x4000 --prefix ge2_layout

"${PSP_RECOMP}" "${GE2_GAME_DIR}/god_g000_Field.sprx" \
  --auto generated-modules/field 0x08E00000 0x4000 --prefix ge2_field

echo "AOT generation finished. The Layout and Field bases are provisional."
echo "Do not register their corpora until the runtime PRX load addresses are verified."
