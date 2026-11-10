# DyausPita

Native static-recompilation port of **God Eater 2 PSP** for Android and desktop, built on [PortableKit](https://github.com/eldaxe/PortableKit).

The supported title identity is **God Eater 2 PSP**. The identifiers ULJS-00560 and NPJH50832 refer to the same target title in this project context; executable identity is verified by SHA-256, not by guessing from the serial alone.

## Repository boundaries

- This repository contains the God Eater 2 profile, game-specific host code, configuration, build scripts and documentation.
- `portablekit/` is the PortableKit framework submodule.
- Game executables, disc images, extracted game assets, generated AOT C++ and save data are not committed. Each developer supplies their own legally obtained game copy and generates derived code locally.

## Current status

Initial repository reconstruction. The profile and integration are being brought up against PortableKit commit `986119616a86104ce7eac557351726c19ee13cd9`. The executable hash and REL2 analysis are recorded in the project notes; encryption metadata, save layout, overlay slots and runtime boot behavior must be verified before claiming a working build.

See [docs/STATUS.md](docs/STATUS.md) for the staged bring-up plan.
