#include "UIElements/UIColorPicker.hpp"

UIColorPicker::UIColorPicker(std::string imagePath, std::string borderPath) {
  this->colorIMG.loadFromFile(RESOURCE_PATH + "color_textures/" + imagePath);
  this->colorTX.loadFromImage(this->colorIMG);
  this->colorSP.setTexture(this->colorTX);
  this->borderTX.loadFromFile(RESOURCE_PATH + "borders/" + borderPath);
  this->borderSP.setTexture(this->borderTX);

  sf::FloatRect colorRect = this->colorSP.getGlobalBounds();
  sf::Vector2f borderPos = this->borderSP.getPosition();
  sf::FloatRect borderSize = this->borderSP.getGlobalBounds();
  this->colorSP.setOrigin(colorRect.width/2, colorRect.height/2);
  this->colorSP.setPosition(borderPos.x + (borderSize.width*0.5), borderPos.y + (borderSize.height*0.5));

  // For a save small overlap, ugly: should be relative to window size
  this->borderSP.scale(0.97, 0.97);

  this->releaseSoundBuffer.loadFromFile(RESOURCE_PATH + "test_sounds/softair.wav");
  this->releaseSound.setBuffer(this->releaseSoundBuffer);
  this->releaseSound.setPitch(1.5);
}

UIColorPicker::UIColorPicker(sf::Image image, std::string borderPath) {
  this->colorTX.loadFromImage(image);
  this->colorSP.setTexture(this->colorTX);

  this->borderTX.loadFromFile(RESOURCE_PATH + "borders/" + borderPath);
  this->borderSP.setTexture(this->borderTX);

  sf::FloatRect colorRect = this->colorSP.getGlobalBounds();
  this->colorSP.setOrigin(colorRect.width/2, colorRect.height/2);

  // For a save small overlap
  this->borderSP.scale(0.97, 0.97);

  this->colorIMG = image;
}

void UIColorPicker::draw() {
  RenderEngine& render_engine = RenderEngine::getInstance();
  render_engine.gameWindow.draw(this->colorSP);
  render_engine.gameWindow.draw(this->borderSP);
}

void UIColorPicker::setPosition(float x, float y) {
  this->borderSP.setPosition(x, y);
  sf::FloatRect borderSize = this->getSize();
  this->colorSP.setPosition(x + (borderSize.width/2), y + (borderSize.height/2)- borderSize.height*0.01);
}

sf::Vector2f UIColorPicker::getPosition() {
  return this->borderSP.getPosition();
}

sf::FloatRect UIColorPicker::getSize() {
  return this->borderSP.getGlobalBounds();
}

void UIColorPicker::scale(float x, float y) {
  sf::Vector2f pos = this->getPosition();
  this->borderSP.scale(sf::Vector2f(x, y));
  this->colorSP.scale(sf::Vector2f(x, y));
  //this->setPosition(pos.x, pos.y);
}

sf::Color UIColorPicker::getPixelColor(sf::Vector2f pos) {
  sf::FloatRect colorSize = this->colorSP.getGlobalBounds();
  sf::Vector2f offset = this->colorSP.getPosition() - sf::Vector2f(colorSize.width/2, colorSize.height/2);
  sf::Vector2f scale = this->colorSP.getScale();
  sf::Vector2f posImg = pos - offset;
  posImg.x /= scale.x;
  posImg.y /= scale.y;
  return this->colorIMG.getPixel(posImg.x, posImg.y);
}

bool UIColorPicker::clickListener(sf::Vector2f &clickedPos) {
  Game& game = Game::getInstance();
  if (game.gameEvents.mousePressed && this->colorSP.getGlobalBounds().contains(game.gameEvents.pressedPos)) {
    this->pressed = true;
  } else if (game.gameEvents.mousePressed){
    this->pressed = false;
  }
  if (this->pressed) {
    if (game.gameEvents.mouseReleased) {
      this->pressed = false;
      if (this->colorSP.getGlobalBounds().contains(game.gameEvents.releasedPos)) {
        clickedPos = sf::Vector2f(game.gameEvents.releasedPos.x, game.gameEvents.releasedPos.y);
        this->releaseSound.play();
        return true;
      }
    }
  }
  clickedPos = sf::Vector2f(0., 0.);
  return false;
}

void UIColorPicker::setColorBox(std::string picPath, std::string borderPath) {
  this->colorIMG.loadFromFile(RESOURCE_PATH + "color_textures/" + picPath);
  this->colorTX.loadFromImage(this->colorIMG);
  this->borderTX.loadFromFile(RESOURCE_PATH + "borders/" + borderPath);
}

void UIColorPicker::setColorImage(std::string picPath) {
  this->colorIMG.loadFromFile(RESOURCE_PATH + "color_textures/" + picPath);
  this->colorTX.loadFromImage(this->colorIMG);
}

void UIColorPicker::setColorImage(sf::Image image) {
  this->colorIMG = image;
  this->colorTX.loadFromImage(this->colorIMG);
}

void UIColorPicker::refreshColorTX() {
  this->colorTX.loadFromImage(this->colorIMG);
}