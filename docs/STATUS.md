# DyausPita bring-up status

## Recovered profile facts

The previous `ge2native.zip` archive contains the complete profile for the Japanese God Eater 2 PSP release:

- `PARAM.SFO`: DISC_ID `NPJH50832`, title `GOD EATER 2`, APP_VER `01.30`.
- The patched-disc EBOOT is a plain ELF. SHA-256: `8b48d9fb6470c221f94b0d852aa45061d043e92f497abbf2e243e4471f4c6efd`.
- Main load base `0x08804000`, guest RAM 32 MiB.
- Save folder `NPJH50832data`; the game requests `ms0:/PSP/SAVEDATA/NPJH50832data/DATA.RDP`.
- `adhoc_product_code = NPJH50832` is provisional.
- `overlay_slots` is empty. `layout` and `god_g000_Field` are PRX modules, not MWo3 overlays.

## AOT analysis recovered

| Image | Functions | Imports | Address units |
|---|---:|---:|---:|
| EBOOT | 12,999 | 367 | 100 |
| layout PRX | 5,109 | 256 | 59 |
| god_g000_Field PRX | 12,487 | 953 | 72 |

The previous EBOOT generation completed all 19,526 automatic functions in 124 non-empty shards over 197 address units (span `0x4000`). The uncompressed C++ output was 3,756,817,312 bytes. This is code generation evidence only; it does not mean those sources have been compiled or linked into the runtime.

## Important PortableKit finding: PRX loading already exists

Inspection of the pinned PortableKit `host/hle/hle_system.cpp` shows that the current runtime already has a partial real PRX loader:

- `sceKernelLoadModule` and `sceKernelLoadModuleNpDrm` share a path.
- Plain ELF PRX files are read, parsed, allocated in guest memory and relocated.
- The loader scans PRX imports and exports, registers guest exports and import stubs, and tracks the module UID, GP, start/stop functions and allocation.
- `sceKernelStartModule`, `sceKernelStopModule` and `sceKernelUnloadModule` have lifecycle handling.
- The loader logs actual allocated base, relocation totals, invalid relocations and unsupported relocations.

However, the PRX loader does **not** register a recompiled AOT corpus for the loaded module. Its guest code therefore executes through the interpreter unless a separate AOT integration is added. The stock encrypted Sony module path is also distinct: some encrypted wrappers are deliberately handled as HLE modules, and the loader does not claim to load them as executable PRXs.

This changes the next engineering task: do not rewrite the whole PRX loader or mistake the staged module corpora for already active AOT. Add a module-corpus seam to PortableKit, then connect DyausPita's Layout and Field corpora to the actual runtime load base.

## Field PRX relocation evidence

The archived Field PRX uses PT_PSPREL2 (type `0x700000A1`) and has no section headers. The previous offline REL2-to-A0 conversion produced 57,439 relocation entries. The saved analysis reported zero invalid and zero unsupported relocations for the converted image. A later byte-level differential simulation against PortableKit's A0 relocation algorithm at the chosen base found no differences. That is not an on-device loader test.

## Provisional module bases

The old AOT staging used `layout = 0x08C00000` and `god_g000_Field = 0x08E00000`. These were selected to avoid the main EBOOT image; they are **not** verified PSP runtime load addresses. PortableKit currently chooses a runtime block for each PRX. Any AOT module registration must either relocate/rebase generated code correctly or deliberately reserve and validate the matching module base. Do not silently assume the staged base is the runtime base.

## Known integration gaps

1. The main target discovers `generated/*.cpp`; it does not automatically discover `generated-modules/layout` or `generated-modules/field`.
2. The module loader has no PRX AOT corpus registration callback yet.
3. The AOT output must be built as separate loadable module corpora or another well-defined mechanism; it must not be merged into the EBOOT corpus directory.
4. The character-rendering crash after player-name entry remains unresolved. It may involve Field/Layout module execution, GE commands, unsupported Allegrex instructions, or renderer state; current evidence does not isolate it.
5. `adhoc_product_code` remains provisional.

## Next work

1. Add a PortableKit PRX corpus ABI that can register a module corpus against its actual runtime base and unregister it on unload.
2. Build Layout and Field corpora as separate modules, retaining the EBOOT corpus as the main executable corpus.
3. Trace actual PRX load bases, module names, imports, exports and lifecycle on device.
4. Run with strict HLE and bounded dispatches; compare interpreter-only and AOT-enabled behavior.
5. Investigate the character-rendering crash only after the module execution path is known.

No disc image, EBOOT, PRX, extracted game assets, generated AOT sources or saves belong in this repository.