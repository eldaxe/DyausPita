# DyausPita

Native static-recompilation port of **God Eater 2 PSP** for Android and desktop, built on [PortableKit](https://github.com/eldaxe/PortableKit).

**Target release:** Japanese PSP release, `NPJH50832`, APP_VER `01.30` (PARAM.SFO identity recorded in the recovered project archive). The earlier ULJS-00560 reference is treated as the same title context, but this profile targets the verified `NPJH50832` dump.

## Repository boundaries

- Game-specific profile, NID names, host code, build workflow and documentation live here.
- `portablekit/` is the PortableKit submodule pinned to `986119616a86104ce7eac557351726c19ee13cd9`.
- Game executables, disc images, extracted assets, generated AOT C++ and save data stay local and are not committed.

## Current status

The initial profile and NID table have been restored from the previous `ge2native.zip` project archive. The EBOOT hash and main AOT corpus generation report are also available. The generated code has not yet been compiled or linked into a working runtime, and the Layout/Field PRX corpora are not yet wired into PortableKit's module loading path.

See [docs/STATUS.md](docs/STATUS.md) and [docs/BUILDING.md](docs/BUILDING.md).