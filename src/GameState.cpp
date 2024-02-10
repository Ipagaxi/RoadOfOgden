#include "GameState.hpp"

GameState::GameState(sf::RenderWindow &window, ActivityEnum activity) {
    gameWindow = &window;
    textures = Textures();
    currentActivity = activity;
}

void GameState::setCurrentActivity(std::unique_ptr<Activity> newActivity) {
    curActivity = std::make_unique<Activity>(*newActivity);
}
