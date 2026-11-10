# DyausPita bring-up status

## Verified project inputs

- Target: God Eater 2 PSP, ULJS-00560 / NPJH50832 (same title as established for this project).
- PSPRecomp executable SHA-256 recorded in the prior analysis: `8b48d9fb6470c221f94b0d852aa45061d043e92f497abbf2e243e4471f4c6efd`.
- Original `god_g000_Field.sprx` SHA-256: `201d69064985df9c941ac0e5d54481ea0376a673437cd8ed1aae844d95952014`.
- REL2 stream in that Field module decoded to 57,439 relocations with no parser errors. The Python differential simulation of the PortableKit A0 algorithm and REL2 behavior produced no differing relocated bytes at load base `0x08804000`.
- The differential test was a simulation of the observed algorithms, not an on-device runtime test.

## Staged implementation

1. Establish a buildable profile-only checkout against a pinned PortableKit submodule.
2. Verify the actual decrypted EBOOT ELF identity, PSP module metadata, imports, load image and memory requirements.
3. Run the game under the interpreter with rendering/audio disabled; collect missing HLE calls and deterministic stop reasons.
4. Bring up title and module loading before compiling the full AOT corpus.
5. Add and validate runtime overlay slots and per-module AOT registration for Layout and Field.
6. Investigate GE commands and unsupported instruction clusters using runtime traces, not corpus counts alone.
7. Test character creation and the character-render path; then enable audio/video and renderer features incrementally.

## Not yet verified

- Encrypted EBOOT SHA-256, decryption tag/key and installer compatibility.
- PARAM.SFO's exact DISC_ID string for the supplied dump.
- Save folder names, disc-file aliases, memory-stick paths and product code.
- EBOOT overlay slot addresses and the runtime lifecycle of Layout/Field PRXs.
- Whether the current runtime can boot this title without additional HLE or renderer work.

Do not treat empty profile fields or placeholder metadata as proof that installation or gameplay works. Do not commit game executables, disc images, extracted assets or generated game-derived C++.
