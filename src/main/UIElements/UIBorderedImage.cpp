#include "UIElements/UIBorderedImage.hpp"

UIBorderedImage::UIBorderedImage(std::string imageFilePath, std::string borderFilePath) {
  this->imageTX.loadFromFile(RESOURCE_PATH + imageFilePath);
  this->imageSP.setTexture(this->imageTX);
  this->borderTX.loadFromFile(RESOURCE_PATH + borderFilePath);
  this->borderSP.setTexture(this->borderTX);

  sf::FloatRect imageRect = this->imageSP.getGlobalBounds();
  sf::Vector2f borderPos = this->borderSP.getPosition();
  sf::FloatRect borderSize = this->borderSP.getGlobalBounds();
  this->imageSP.setOrigin(imageRect.width/2.f, imageRect.height/2.f);
  this->imageSP.setPosition(borderPos.x + (borderSize.width/2.f), borderPos.y + (borderSize.height/2.f));

  // For a save small overlap
  this->borderSP.scale(0.97, 0.97);
}


void UIBorderedImage::init(std::string imageFilePath, std::string borderFilePath) {
  this->imageTX.loadFromFile(RESOURCE_PATH + imageFilePath);
  this->imageSP.setTexture(this->imageTX);
  this->borderTX.loadFromFile(RESOURCE_PATH + borderFilePath);
  this->borderSP.setTexture(this->borderTX);

  sf::FloatRect imageRect = this->imageSP.getGlobalBounds();
  sf::Vector2f borderPos = this->borderSP.getPosition();
  sf::FloatRect borderSize = this->borderSP.getGlobalBounds();
  this->imageSP.setOrigin(imageRect.width/2.f, imageRect.height/2.f);
  this->imageSP.setPosition(borderPos.x + (borderSize.width/2.f), borderPos.y + (borderSize.height/2.f));

  // For a save small overlap
  this->borderSP.scale(0.97, 0.97);
}

void UIBorderedImage::setImage(std::string imagePath) {
  this->imageTX.loadFromFile(RESOURCE_PATH + imagePath);
  this->imageSP.setTexture(this->imageTX);
}

void UIBorderedImage::draw() {
  Game& game = Game::getInstance();
  game.gameWindow.draw(this->imageSP);
  game.gameWindow.draw(this->borderSP);
}

void UIBorderedImage::setPosition(float x, float y) {
    this->borderSP.setPosition(x, y);
    sf::FloatRect borderSize = this->getSize();
    this->imageSP.setPosition(x + (borderSize.width/2.f), y + (borderSize.height/2.f));
}

sf::Vector2f UIBorderedImage::getPosition() {
    return this->borderSP.getPosition();
}

sf::FloatRect UIBorderedImage::getSize() {
    return this->borderSP.getGlobalBounds();
}

void UIBorderedImage::scale(float x, float y) {
    this->borderSP.scale(sf::Vector2f(x, y));
    this->imageSP.scale(sf::Vector2f(x, y));
}