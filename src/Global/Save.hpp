#ifndef SAVE_HPP
#define SAVE_HPP

#include <filesystem>
#include <iostream>

#include "Global/Utility.hpp"

namespace fs = std::filesystem;

namespace SaveState {
    void create_game_state_if_no_exist();
}

#endif