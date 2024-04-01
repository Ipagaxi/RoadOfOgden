#include "GameState.hpp"

GameState::GameState(sf::RenderWindow &window, ActivityEnum activity) : renderEngine(&window) {

    gameWindow = &window;

    this->mainFont.loadFromFile(RESOURCE_PATH "fonts/Avara-Bold.otf");
}