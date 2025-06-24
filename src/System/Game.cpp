#include "Game.hpp"

Game &Game::getInstance() {
  if (!instance) {
    instance = new Game();
  }
  return *instance;
}

Game::Game() {
  //sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Road of Ogden", sf::Style::Fullscreen);

  this->mainFont.loadFromFile(RESOURCE_PATH + "fonts/Avara-Bold.otf");
}

Game::~Game() {
}