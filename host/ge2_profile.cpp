// God Eater 2 (NPJH50832, Japanese release, APP_VER 01.30).
// Recovered from the previous ge2native project archive.
#include "profile.hpp"

#include <array>
#include <cstdlib>

namespace portablekit {
namespace {

constexpr std::array<SaveFolder, 1> kSaveFolders{{
    {"NPJH50832data", "Save data", true},
}};

constexpr std::array<DiscFileAlias, 2> kDiscFileAliases{{
    {"PSP/SAVEDATA/NPJH50832data/DATA.RDP", "PSP_GAME/USRDIR/data.rdp"},
    {"PSP/SAVEDATA/NPJH50832data/PACKAGE.RDP", "PSP_GAME/USRDIR/package.rdp"},
}};

// Capture the caller registers at the entry of the atomic refcount helper.
// The interpreter's existing watch facility logs a0/a1/ra before the prologue
// overwrites ra, which identifies the guest call site without changing code flow.
void enable_atomic_caller_trace(psprecomp::Runtime &, const psprecomp::Elf32Image &) {
#if defined(_WIN32)
    _putenv_s("PSPRECOMP_INTERPRETER_WATCH", "0x0894123C");
#else
    setenv("PSPRECOMP_INTERPRETER_WATCH", "0x0894123C", 0);
#endif
}

constexpr GameProfile kProfile{
    .app_name = "GodEater2Native",
    .project_name = "God Eater 2",
    .env_prefix = "GE2",
    .data_organization = "eldaxe",
    .data_application = "GodEater2",

    .disc_id = "NPJH50832",
    .disc_id_display = "NPJH-50832",
    .game_title = "GOD EATER 2",
    .executable_path_on_disc = "PSP_GAME/SYSDIR/EBOOT.BIN",
    .param_sfo_path_on_disc = "PSP_GAME/PARAM.SFO",
    .release_name = "the Japanese release",
    .encrypted_executable_sha256 =
        "8b48d9fb6470c221f94b0d852aa45061d043e92f497abbf2e243e4471f4c6efd",
    .executable_sha256 =
        "8b48d9fb6470c221f94b0d852aa45061d043e92f497abbf2e243e4471f4c6efd",
    .decryption_tag = 0,
    .decryption_key = {},

    .load_base = 0x08804000,
    .guest_ram_bytes = 32u * 1024u * 1024u,
    .boot_path = "disc0:/PSP_GAME/SYSDIR/EBOOT.BIN",
    .overlay_slots = {},

    .save_game_name = "NPJH50832data",
    .save_folders = kSaveFolders,
    .memory_stick_patch_folder = "PATCH-LUMI",
    .disc_file_aliases = kDiscFileAliases,

    // Provisional assumption from the previous profile; verify with a network trace.
    .adhoc_product_code = "NPJH50832",
    .patch_loaded_image = enable_atomic_caller_trace,

    .frame_vblanks = 2,
    .system_language = 0,
    .confirm_button = 0,
};

} // namespace

const GameProfile &game() { return kProfile; }

} // namespace portablekit
