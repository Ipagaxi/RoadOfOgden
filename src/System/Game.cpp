#include "Game.hpp"

Game &Game::getInstance() {
  if (!instance) {
    instance = new Game();
  }
  return *instance;
}

Game::Game(): gameWindow(*(new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Road of Ogden", sf::Style::Fullscreen))) {
  //sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Road of Ogden", sf::Style::Fullscreen);
  this->gameWindow.setFramerateLimit(60);
  this->mainFont.loadFromFile(RESOURCES + "fonts/Avara-Bold.otf");
}

Game::~Game() {
}