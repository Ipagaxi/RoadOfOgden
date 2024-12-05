#include "Save.hpp"

nlohmann::json starting_player_stats = {
  {"name", "Arnold"},
  {"level", 1},
  {"experience", 0}
};

std::string get_save_dir_path() {
  return get_bundle_dir_path() + "save/";
}

std::string get_game_state_save_dir_path() {
    return SAVE_PATH + "game_state/";
}

std::string get_player_save_dir_path() {
    return GAME_STATE_SAVE_PATH + "player/";
}

void create_player_save_state() {
    SaveState::write_save_state(PLAYER_SAVE_PATH + "stats.json", starting_player_stats);
}

void load_game_state_from_file() {
    
}

void create_game_state() {
    fs::create_directory(GAME_STATE_SAVE_PATH);
        fs::create_directories(PLAYER_SAVE_PATH);
        create_player_save_state();
}

void SaveState::check_game_state() {
    if (fs::exists(GAME_STATE_SAVE_PATH)) {
        load_game_state_from_file();
    } else {
        create_game_state();
    }
}

void SaveState::write_save_state(std::string file_path, nlohmann::json json_data) {
    std::fstream file;
    file.open(file_path, std::ios::out);
    file << json_data;
    file.close();
}