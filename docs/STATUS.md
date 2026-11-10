# DyausPita bring-up status

## Recovered profile facts

The previous `ge2native.zip` archive contains a complete profile for the Japanese God Eater 2 PSP release:

- `PARAM.SFO`: DISC_ID `NPJH50832`, title `GOD EATER 2`, APP_VER `01.30`.
- EBOOT is a plain ELF on the patched disc; the recovered profile records SHA-256 `8b48d9fb6470c221f94b0d852aa45061d043e92f497abbf2e243e4471f4c6efd` for both encrypted/on-disc and decrypted executable fields.
- Main load base `0x08804000`, guest RAM `32 MiB`.
- Save folder `NPJH50832data`; the game requests `ms0:/PSP/SAVEDATA/NPJH50832data/DATA.RDP`.
- `adhoc_product_code = NPJH50832` is explicitly provisional in the source archive.
- Profile keeps `overlay_slots` empty: `layout` and `god_g000_Field` are separate PRX modules, not MWo3 overlays.

The recovered `config/nids.csv` lists the game imports that PortableKit's built-in NID table does not name. These names were read from the previous PPSSPP HLE registration analysis.

## AOT corpus evidence

The previous project archive reports the following analysis:

| Image | Functions | Imports | Generated address units |
|---|---:|---:|---:|
| EBOOT | 12,999 | 367 | 100 |
| layout PRX | 5,109 | 256 | 59 |
| god_g000_Field PRX | 12,487 | 953 | 72 |

The main EBOOT's 19,526 automatic functions were generated in 124 non-empty shards across 197 address units (span `0x4000`). The uncompressed C++ output was 3,756,817,312 bytes. The report explicitly says this confirms code generation only; the shards have not been compiled or linked into the Android runtime.

The previous project reports that `god_g000_Field` uses PT_PSPREL2 and lacks section headers. Its offline conversion to A0 was checked by `psp_analyze` with 0 invalid and 0 unsupported relocations. A later differential simulation found no relocated-byte differences against the PortableKit algorithm at load base `0x08804000`; that simulation is not a device/runtime test. Do not infer that the actual runtime module base is `0x08804000`.

## Known integration gaps

1. PortableKit's current `portablekit_add_game()` automatically discovers only `${PROFILE_DIR}/generated/*.cpp` for the main executable. The two module corpora are staged separately and require explicit module/overlay integration.
2. Chosen historical PRX corpus bases were `layout = 0x08C00000` and Field `0x08E00000`; they are provisional, not measured runtime load addresses. Confirm from module-loader traces before registering those corpora.
3. The previous project README says no interpreter boot or device build had been run at that point.
4. The crash after player-name entry and during character rendering remains unresolved. Investigate module load addresses, imported game-module exports, GE command behavior and unsupported instructions with runtime traces.
5. `adhoc_product_code` remains provisional.

## Next work

1. Build the profile-only host against the pinned PortableKit revision.
2. Confirm the installer accepts the user's exact EBOOT and PARAM.SFO.
3. Run interpreter-only with `GE2_NO_RENDER=1`, `GE2_NO_AUDIO=1`, and bounded timeout; capture stubs and module load traces.
4. Implement and test module loading and module AOT registration for Layout and Field.
5. Run through character creation and isolate the first failure before tuning renderer/audio/video.

No game-derived executable, disc data, extracted assets or generated AOT source belongs in this repository.