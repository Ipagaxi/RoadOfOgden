#include "Activities/Activity.hpp"

Activity::Activity() {
  Game& game = Game::getInstance();
  sf::Vector2u windowSize = game.gameWindow.getSize();
  sf::FloatRect buttonSize = this->exitButton.getSize();
  this->exitButton.setPosition(windowSize.x * 0.99 - buttonSize.width, windowSize.x * 0.01);
}

Activity::~Activity() {
}

ActivityEnum Activity::executeActivity() {
  return ActivityEnum::Menu;
}