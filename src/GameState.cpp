#include "GameState.hpp"

/*
std::vector<sf::Texture> GameState::initTextures() {
    
}*/

GameState::GameState(sf::RenderWindow &window, ActivityEnum activity) {
    gameWindow = &window;
    textures = Textures();
    currentActivity = activity;
}

/*void GameState::changeActivity(std::unique_ptr<Activity> newActivity) {
    currentActivity = std::move(newActivity);
}*/

/*void GameState::displayCurrentActivity() {
    currentActivity->displayActivity(*this);
}*/
