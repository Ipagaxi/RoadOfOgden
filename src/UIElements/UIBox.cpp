#include "UIElements/UIBox.hpp"

UIBox::UIBox(sf::Color fillColor, std::string borderFilePath) {
    this->borderTX.loadFromFile(RESOURCE_PATH + borderFilePath);

    this->borderSP.setTexture(this->borderTX);

    sf::FloatRect borderSize = this->borderSP.getGlobalBounds();
    this->backgroundREC.setSize(sf::Vector2f(borderSize.width * 0.96, borderSize.height * 0.95));
    this->backgroundREC.setFillColor(fillColor);
    sf::FloatRect backgroundSize = this->backgroundREC.getGlobalBounds();
    this->backgroundREC.setOrigin(backgroundSize.width/2, backgroundSize.height/2);
}

void UIBox::draw() {
  RenderEngine& render_engine = RenderEngine::getInstance();
  render_engine.gameWindow.draw(this->backgroundREC);
  render_engine.gameWindow.draw(this->borderSP);
}

sf::FloatRect UIBox::getSize() {
    return this->borderSP.getGlobalBounds();
}
        
void UIBox::setPosition(float x, float y) {
    this->borderSP.setPosition(x, y);
    sf::FloatRect borderSize = this->getSize();
    this->backgroundREC.setPosition(x + (borderSize.width/2), y + (borderSize.height/2));
}

sf::Vector2f UIBox::getPosition() {
    return this->borderSP.getPosition();
}

void UIBox::scale(float x, float y) {
    this->borderSP.scale(sf::Vector2f(x, y));
    this->backgroundREC.scale(sf::Vector2f(x, y));
}

// 
void UIBox::setBackgroundMargin(float x, float y) {
    sf::Vector2f backgroundRECSize = this->backgroundREC.getSize();
    sf::Vector2f currentScale = this->backgroundREC.getScale();
    sf::Vector2f newSize = sf::Vector2f(backgroundRECSize.x - (2*x / currentScale.x), backgroundRECSize.y - (2*y / currentScale.y));
    this->backgroundREC.setSize(newSize);
    this->backgroundREC.setOrigin(newSize.x * 0.5, newSize.y * 0.5);
}