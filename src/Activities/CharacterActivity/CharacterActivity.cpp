#include "CharacterActivity.hpp"

CharacterActivity::CharacterActivity(): Activity() {
  this->backgroundTX.loadFromFile(RESOURCE_PATH + "backgrounds/backgroundMenu.png");
  this->backgroundSP.setTexture(this->backgroundTX);
}

ActivityEnum CharacterActivity::executeActivity() {
  Game& game = Game::getInstance();
  ActivityEnum currentActivity = ActivityEnum::Character;
  game.gameWindow.draw(this->backgroundSP);
  this->exitButton.draw();
  if (this->exitButton.clickListener()) {
    currentActivity = ActivityEnum::Menu;
  }
  return currentActivity;
}