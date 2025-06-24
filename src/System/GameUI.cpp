#include "GameUI.hpp"

GameUI* GameUI::instance = nullptr;

GameUI& GameUI::getInstance() {
  if (!instance) {
    instance = new GameUI();
  }
  return *instance;
}

GameUI::GameUI() {
  this->backgroundTX.loadFromFile(RESOURCE_PATH + "backgrounds/backgroundMenu.png");
  this->backgroundSP.setTexture(this->backgroundTX);
}

void GameUI::changeBackgroundTexture(std::string filename) {
  this->backgroundTX.loadFromFile(RESOURCE_PATH + "backgrounds/" + filename);
  this->backgroundSP.setTexture(this->backgroundTX);
}

