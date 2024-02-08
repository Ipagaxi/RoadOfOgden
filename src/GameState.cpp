#include "GameState.hpp"

/*
std::vector<sf::Texture> GameState::initTextures() {
    
}*/

GameState::GameState(sf::RenderWindow &window) {
    gameWindow = &window;
    textures = Textures();
}
