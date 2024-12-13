#include "Save.hpp"

nlohmann::json starting_player_stats = {
  {"name", "Arnold"},
  {"level", 1},
  {"experience", 0},
  {"equipped_items", nlohmann::json::array()},
  {"inventory_items", nlohmann::json::array()}
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

void to_json(nlohmann::json& j, const Item& i) {
        j = nlohmann::json{{"name", i.name}};
    }

void from_json(const nlohmann::json& j, Item& i) {
    j.at("name").get_to(i.name);
}

/*void to_json(nlohmann::json& j, const Player& p) {
        j = nlohmann::json{{"name", p.get_name()}, {"level", p.level}, {"experience", p.experience}, {"equipped_items", p.equipped_items}};
}

void from_json(const nlohmann::json& j, Player& p) {
    j.at("name").get_to(p.name);
    j.at("level").get_to(p.level);
    j.at("experience").get_to(p.experience);
    j.at("equipped_items").get_to(p.equipped_items);
    j.at("inventory_items").get_to(p.inventory_items);
}*/

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

void SaveState::save_player_state() {
    GameState& game_state = GameState::getInstance();
    Player player = *(game_state.player);
    nlohmann::json player_stats = {
        {"name", player.get_name()},
        {"level", player.get_level()},
        {"experience", player.get_experience()},
        {"equipped_items", player.get_equipped_items()},
        {"inventory_items", player.get_inventory_items()}
    };
    SaveState::write_save_state(PLAYER_STATS_SAVE_PATH, player_stats);
}

void create_player_save_state() {
    SaveState::write_save_state(PLAYER_STATS_SAVE_PATH, starting_player_stats);
}

void load_player_from_file() {
    GameState& game_state = GameState::getInstance();
    // A template structure would be beneficial for the structure of the stats json
    nlohmann::json player_stats_json = SaveState::read_save_state(PLAYER_STATS_SAVE_PATH);
    //Player player = Player(player_stats_json["name"], player_stats_json["level"], player_stats_json["experience"], "default_actor_quer.png");


    game_state.player->set_name(player_stats_json["name"].template get<std::string>());
    game_state.player->set_level(player_stats_json["level"].template get<int>());
    game_state.player->set_experience(player_stats_json["experience"].template get<int>());
    game_state.player->set_equipped_items(player_stats_json["equipped_items"].template get<std::vector<Item>>());
    game_state.player->set_inventory_items(player_stats_json["inventory_items"].template get<std::vector<Item>>());

    //Player loaded_player = player_stats_json.template get<Player>();
    //game_state.update_player(loaded_player);
    // How to load the read player from the file to the game state player?
}

void load_game_state_from_file() {
    load_player_from_file();
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