#include "GameState.hpp"

/*
std::vector<sf::Texture> GameState::initTextures() {
    
}*/

GameState::GameState(sf::RenderWindow &window) : currentActivity(std::make_unique<FightActivity>()){
    gameWindow = &window;
    textures = Textures();
}

void GameState::changeActivity(std::unique_ptr<Activity> newActivity) {
    currentActivity = std::move(newActivity);
}

void GameState::startActivity(sf::RenderWindow &window, sf::Texture &background, sf::Texture &gear) {
    currentActivity->displayActivity(window, background, gear);
}
