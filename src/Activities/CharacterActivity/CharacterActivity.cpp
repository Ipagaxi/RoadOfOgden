#include "CharacterActivity.hpp"

CharacterActivity::CharacterActivity(): Activity() {
  this->backgroundTX.loadFromFile(RESOURCE_PATH + "backgrounds/backgroundMenu.png");
  this->backgroundSP.setTexture(this->backgroundTX);
}

ActivityEnum CharacterActivity::executeActivity() {
  RenderEngine& render_engine = RenderEngine::getInstance();
  ActivityEnum currentActivity = ActivityEnum::Character;
  render_engine.gameWindow.draw(this->backgroundSP);
  this->exitButton.draw();
  if (this->exitButton.clickListener()) {
    currentActivity = ActivityEnum::Menu;
  }
  return currentActivity;
}