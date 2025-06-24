#ifndef SAVE_HPP
#define SAVE_HPP

#include <filesystem>
#include <iostream>
#include <fstream>
#include "Lib/nlohmann_json/json.hpp"

#include "Global/Utility.hpp"
#include "Actors/Player.hpp"
#include "System/GameState.hpp"
#include "Items/Item.hpp"

namespace fs = std::filesystem;

std::string get_save_dir_path();
std::string const SAVE_DIR_PATH = get_save_dir_path();

std::string get_game_state_save_dir_path();
std::string const GAME_STATE_SAVE_DIR_PATH = get_game_state_save_dir_path();

std::string get_player_save_dir_path();
std::string const PLAYER_SAVE_DIR_PATH = get_player_save_dir_path();

std::string get_player_stats_save_path();
std::string const PLAYER_STATS_SAVE_PATH = get_player_stats_save_path();


namespace SaveState {
    void write_save_state(std::string file_path, nlohmann::json json_data);
    nlohmann::json read_save_state(std::string file_path);

    void save_player_state();

    void check_game_state();
}

#endif