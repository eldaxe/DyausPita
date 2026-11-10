# Building DyausPita

## Checkout

```sh
git clone --recurse-submodules https://github.com/eldaxe/DyausPita.git
cd DyausPita
git submodule update --init --recursive
```

The PortableKit submodule is pinned to `986119616a86104ce7eac557351726c19ee13cd9`.

## Host build (profile scaffold)

Requirements: CMake 3.20+, Ninja, a C++20 compiler, Python 3, and the dependencies described by PortableKit. The renderer is optional for a headless profile build.

```sh
cmake -S . -B out -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DPORTABLEKIT_RENDERER=OFF \
  -DPSPRECOMP_BUILD_TESTS=OFF \
  -DPSPRECOMP_GENERATED_JOBS=1
cmake --build out --target DyausPitaNative -j1
```

This checks the host/profile integration only. It does not prove the game boots. Do not run the installer until the exact dump's PARAM.SFO and EBOOT hashes have been checked.

## Generate main EBOOT AOT locally

After building PortableKit's `psp_recomp` tool and preparing the decrypted EBOOT from the user's own dump:

```sh
mkdir -p generated
psp_recomp game/EBOOT.BIN --auto generated 0x08804000 0x4000

psp_recomp game/layout.bin --auto generated-modules/layout 0x08C00000 0x4000 --prefix ge2_layout
psp_recomp game/god_g000_Field.sprx --auto generated-modules/field 0x08E00000 0x4000 --prefix ge2_field
```

The previous project generated 19,526 functions in 124 non-empty address shards. The uncompressed C++ corpus is about 3.76 GB. It is not stored in this repository and has not yet been compiled/linked as a working game build.

The Layout and Field module corpora are separate and use the `--prefix` option to avoid generated symbol collisions. The previous generation used chosen bases `0x08C00000` and `0x08E00000`, but the live loader addresses have not been verified. Do not place these corpora into the main `generated/` directory: PortableKit's current game target discovers that directory as the main executable corpus only. Module integration is a separate task.

## Android

Android app packaging is not yet wired into this reconstructed repository. First establish a clean host build and interpreter boot; then integrate the Android NDK/SDL3/Vulkan toolchain and APK packaging from the pinned PortableKit revision.