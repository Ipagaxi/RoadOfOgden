#include "UIObjects/UIEnemyOverview.hpp"

UIEnemyOverview::UIEnemyOverview(std::shared_ptr<Enemy> _enemy): enemyBorderedImage("monster_landscape_cut/" + (*_enemy).picPath, "actor_borders/fight_border.png"), enemyStats(_enemy) {
  Game& game = Game::getInstance();
  this->enemy = *_enemy;

  sf::Vector2u windowSize = game.gameWindow.getSize();
  sf::FloatRect boxRect = this->box.getSize();
  sf::Vector2f overviewPos = sf::Vector2f(windowSize.x * 0.51, windowSize.y * 0.1);
  this->box.setPosition(overviewPos.x, overviewPos.y);

  float relativeOuterPaddingStatBoxes = 0.05;
  sf::FloatRect statsBoxSize = this->enemyStats.getSize();
  this->enemyStats.setPosition(windowSize.x * (1.0 - relativeOuterPaddingStatBoxes) - statsBoxSize.width, windowSize.y * 0.35);

  sf::FloatRect creatureFrameRect = this->enemyBorderedImage.getSize();
  float creatureBoxScale = (windowSize.x*0.22)/creatureFrameRect.width;
  this->enemyBorderedImage.scale(creatureBoxScale, creatureBoxScale);
  creatureFrameRect = this->enemyBorderedImage.getSize();
  float creatureFrameMargin = boxRect.width * 0.05;
  sf::Vector2f creatureFramePos = sf::Vector2f(overviewPos.x + creatureFrameMargin, overviewPos.y + creatureFrameMargin);
  this->enemyBorderedImage.setPosition(creatureFramePos.x, creatureFramePos.y);

  this->enemyIconBackgroundTX.loadFromFile(RESOURCE_PATH "actor_landscape_backgrounds/forest.png");
  this->enemyIconBackgroundSP.setTexture(this->enemyIconBackgroundTX);
  sf::FloatRect creatureBackgroundRect = this->enemyIconBackgroundSP.getGlobalBounds();
  this->enemyIconBackgroundSP.setOrigin(creatureBackgroundRect.width / 2.f, creatureBackgroundRect.height / 2.f);
  this->enemyIconBackgroundSP.setPosition(creatureFramePos.x + creatureFrameRect.width / 2.f, creatureFramePos.y + creatureFrameRect.height / 2.f);
  this->enemyIconBackgroundSP.scale(creatureBoxScale, creatureBoxScale);

  float colorPickerScale = creatureFrameRect.width / colorPicker.getSize().width;
  this->colorPicker.scale(colorPickerScale, colorPickerScale);
  this->colorPicker.setColorBox(this->enemy.colorPicPath, this->enemy.colorPicBorderPath);
  sf::Vector2f colorPickerPos = sf::Vector2f(creatureFramePos.x, creatureFramePos.y  + creatureFrameRect.height + boxRect.height * 0);
  this->colorPicker.setPosition(colorPickerPos.x, colorPickerPos.y);
  sf::FloatRect colorPickerSize = this->colorPicker.getSize();

  this->pickedColorText.setFont(game.mainFont);
  this->pickedColorText.setString("(0, 0, 0)");
  this->pickedColorText.setCharacterSize(game.gameWindow.getSize().y * 0.04);
  this->pickedColorText.setFillColor(sf::Color::Yellow);
  sf::FloatRect textRec = this->pickedColorText.getGlobalBounds();
  this->pickedColorText.setOrigin(textRec.width/2, textRec.height/2);
  this->pickedColorText.setPosition(colorPickerPos.x + colorPickerSize.width*0.5, colorPickerPos.y + colorPickerSize.height + windowSize.y*0.02);
}

void UIEnemyOverview::draw() {
  Game& game = Game::getInstance();
  this->box.draw();
  this->enemyStats.draw();
  this->colorPicker.draw();
  game.gameWindow.draw(this->pickedColorText);
  game.gameWindow.draw(this->enemyIconBackgroundSP);
  this->enemyBorderedImage.draw();
}

void UIEnemyOverview::changeHealth(int lostHealth) {
  int newHealth = std::max(this->enemy.health - lostHealth, 0);
  this->enemy.health = newHealth;
  this->enemy.notify(this->enemy);
}

void UIEnemyOverview::updatePickedColorText(std::string newText, sf::Color pickedColor) {
  this->pickedColorText.setFillColor(pickedColor);
  this->pickedColorText.setString(newText);
  sf::FloatRect pickedColorTextSize = this->pickedColorText.getGlobalBounds();
  this->pickedColorText.setOrigin(pickedColorTextSize.width * 0.5, pickedColorTextSize.height * 0.5);
}