#include "RenderEngine.hpp"

RenderEngine* RenderEngine::instance = nullptr;

RenderEngine &RenderEngine::getInstance() {
  if (!instance) {
    instance = new RenderEngine();
  }
  return *instance;
}

RenderEngine::RenderEngine(): gameWindow(sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Road of Ogden", sf::Style::Fullscreen)) {
  this->gameWindow.setFramerateLimit(60);
}
