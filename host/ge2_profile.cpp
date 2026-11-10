#include "profile.hpp"

#include <cstdint>

namespace portablekit {
namespace {

// These values are deliberately limited to facts established for this title.
// Save-data folder names, product code, decryption metadata and overlay slots
// must be read from the user's own dump before enabling installation/gameplay.
constexpr SaveFolder kSaveFolders[] = {};

} // namespace

const GameProfile &game() {
    static const GameProfile profile{
        .app_name = "DyausPitaNative",
        .project_name = "DyausPita",
        .env_prefix = "GE2",
        .data_organization = "DyausPita",
        .data_application = "GodEater2",
        .disc_id = "ULJS00560",
        .disc_id_display = "ULJS-00560",
        .game_title = "God Eater 2",
        .executable_path_on_disc = "PSP_GAME/SYSDIR/EBOOT.BIN",
        .param_sfo_path_on_disc = "PSP_GAME/PARAM.SFO",
        .release_name = "Japanese PSP release",
        .encrypted_executable_sha256 = "",
        .executable_sha256 = "8b48d9fb6470c221f94b0d852aa45061d043e92f497abbf2e243e4471f4c6efd",
        .decryption_tag = 0u,
        .decryption_key = {},
        .load_base = 0x08804000u,
        .guest_ram_bytes = 64u * 1024u * 1024u,
        .boot_path = "disc0:/PSP_GAME/SYSDIR/EBOOT.BIN",
        .overlay_slots = {},
        .save_game_name = "ULJS00560",
        .save_folders = kSaveFolders,
        .adhoc_product_code = "",
        .frame_vblanks = 2u,
        .system_language = 0u,
        .confirm_button = 0u,
    };
    return profile;
}

} // namespace portablekit
