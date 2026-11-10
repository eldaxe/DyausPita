# Building DyausPita

## Requirements

Use the toolchain requirements documented by the pinned [PortableKit](https://github.com/eldaxe/PortableKit) revision: CMake 3.20+, Ninja, a C++20 compiler and Python 3. The Vulkan renderer additionally needs SDL3, Vulkan headers/loader and `glslangValidator`; FFmpeg requirements are documented by PortableKit.

## Checkout

```sh
git clone --recurse-submodules https://github.com/eldaxe/DyausPita.git
cd DyausPita
# If the repository was cloned without submodules:
git submodule update --init --recursive
```

The PortableKit submodule is pinned to commit `986119616a86104ce7eac557351726c19ee13cd9`.

## Configure and build the profile scaffold

```sh
cmake -S . -B out -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DPSPRECOMP_BUILD_TESTS=OFF \
  -DPSPRECOMP_GENERATED_JOBS=1
cmake --build out --target DyausPitaNative -j1
```

This initial repository stage is a profile/build scaffold. It does not yet install or boot God Eater 2: the encrypted EBOOT metadata, verified PARAM.SFO identity, save-data layout, overlay-slot table and module-loading integration still need to be completed from the user's own dump and runtime traces.

Do not run the installer against a game image until the profile's encrypted EBOOT hash, decryption tag/key and disc ID have been verified. The executable hash currently recorded is the SHA-256 used by the earlier PSPRecomp analysis; it must be confirmed against the exact decrypted ELF supplied to the build.

## Android

Android app packaging is not wired into this first scaffold yet. The initial target is to make the shared profile and runtime integration build cleanly; Android packaging follows after the host build and interpreter boot path are verified.
