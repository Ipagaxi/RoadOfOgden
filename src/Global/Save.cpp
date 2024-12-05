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
    return SAVE_DIR_PATH + "game_state/";
}

std::string get_player_save_dir_path() {
    return GAME_STATE_SAVE_DIR_PATH + "player/";
}

std::string get_player_stats_save_path() {
    return PLAYER_SAVE_DIR_PATH + "stats.json";
}

void create_player_save_state() {
    SaveState::write_save_state(PLAYER_STATS_SAVE_PATH, starting_player_stats);
}

void load_game_state_from_file() {
    // A template structure would be beneficial for the structure of the stats json
    nlohmann::json player_stats_json = SaveState::read_save_state(PLAYER_STATS_SAVE_PATH);
    Player player = Player(player_stats_json["name"], player_stats_json["level"], player_stats_json["experience"], "default_actor_quer.png");
    GameState::getInstance(player);
}

void create_game_state() {
    fs::create_directory(GAME_STATE_SAVE_DIR_PATH);
        fs::create_directories(PLAYER_SAVE_DIR_PATH);
        create_player_save_state();
}

void SaveState::check_game_state() {
    if (fs::exists(GAME_STATE_SAVE_DIR_PATH)) {
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

nlohmann::json SaveState::read_save_state(std::string file_path) {
    std::ifstream file(file_path);
    nlohmann::json json_data = nlohmann::json::parse(file);
    file.close();
    return json_data;
}