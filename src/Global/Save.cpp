#include "Save.hpp"

void SaveState::create_game_state_if_no_exist() {
    const fs::path game_state_path{SAVE_PATH + "game_state/"};
    if (!fs::exists(game_state_path)) {
        fs::create_directory(game_state_path);
        std::cout << "New directory created" << std::endl;
    }
}