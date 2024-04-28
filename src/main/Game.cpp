#include "Game.hpp"

Game::Game(sf::RenderWindow &window, ActivityEnum activity) : renderEngine(&window) {

    this->mainFont.loadFromFile(RESOURCE_PATH "fonts/Avara-Bold.otf");
}