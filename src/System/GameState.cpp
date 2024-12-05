#include "GameState.hpp"

GameState::GameState(Player player): player(std::make_shared<Player>(player)) {

}

GameState::~GameState(){

}

GameState &GameState::getInstance() {
  if (!instance) {
    // Global Staring values necessary
    instance = new GameState(Player("Arnold", 1, 0, "default_actor_quer.png"));
  }
  return *instance;
}

GameState &GameState::getInstance(Player player) {
    if (!instance) {
        instance = new GameState(player);
    }
    return *instance;
}

GameState* GameState::instance = nullptr;