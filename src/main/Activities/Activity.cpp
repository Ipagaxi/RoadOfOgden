#include "Activities/Activity.hpp"

Activity::Activity(Game &game) {
  sf::Vector2u windowSize = game.renderEngine.gameWindow->getSize();
  sf::FloatRect buttonSize = this->exitButton.getSize();
  this->exitButton.setPosition(windowSize.x * 0.99 - buttonSize.width, windowSize.x * 0.01);
}

Activity::~Activity() {
}

ActivityEnum Activity::executeActivity(Game &game) {
  return ActivityEnum::Menu;
}