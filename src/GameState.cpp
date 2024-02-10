#include "GameState.hpp"

GameState::GameState(sf::RenderWindow &window, ActivityEnum activity) {
    gameWindow = &window;
    textures = Textures();
    //currentActivity = activity;
    counter = 0;
}

void GameState::setCurrentActivity(std::unique_ptr<Activity> newActivity) {
    currentActivity = std::move(newActivity);
}