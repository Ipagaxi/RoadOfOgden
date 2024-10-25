#include "Activities/Activity.hpp"

Activity::Activity() {
  RenderEngine& render_engine = RenderEngine::getInstance();
  sf::Vector2u windowSize = render_engine.gameWindow.getSize();
  sf::FloatRect buttonSize = this->exitButton.getSize();
  this->exitButton.setPosition(windowSize.x * 0.99 - buttonSize.width, windowSize.x * 0.01);
}

Activity::~Activity() {
}

ActivityEnum Activity::executeActivity() {
  return ActivityEnum::Menu;
}