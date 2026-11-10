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

## Android APK (arm64-v8a)

The `.github/workflows/android-apk.yml` workflow builds a **debug bootstrap APK** for 64-bit Android devices and uploads it as the `DyausPita-Android-arm64-debug` artifact. Run it with **Actions → Android APK → Run workflow**, or push to `main`.

The workflow uses the Android NDK, SDL3, Vulkan and PortableKit's existing `packaging/android/build_apk.sh` packager. It targets Android 10 / API 29 and ABI `arm64-v8a`; the manifest requires Vulkan 1.1. The APK is signed with a temporary CI key and is intended for testing, not as a stable update channel.

The repository does **not** contain the user's EBOOT, game assets, or generated AOT C++. The workflow therefore builds the bootstrap runtime with PortableKit's empty generated-code stub. A successful APK build proves native compilation and packaging only; it does not mean God Eater 2 can boot or render. The user must install their own game dump through the app, and the AOT EBOOT plus Layout/Field PRX integration remain separate unfinished work.

To reproduce locally, follow the workflow's CMake options and package with:

```sh
APP_ID=com.eldaxe.godeater2native \
GAME_RES="$PWD/android-res" \
DEBUGGABLE=1 \
portablekit/packaging/android/build_apk.sh \
  out/android .deps/SDL .deps/sdl-install/lib/libSDL3.so \
  out/DyausPita-arm64-debug.apk
```

Do not commit game dumps, save data, generated AOT corpora, signing keys, or release keystores.