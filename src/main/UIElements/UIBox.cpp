#include "UIElements/UIBox.hpp"

UIBox::UIBox() {
    this->borderTX.loadFromFile(RESOURCE_PATH "borders/borderBox.png");

    this->borderSP.setTexture(this->borderTX);

    sf::FloatRect borderSize = this->borderSP.getGlobalBounds();
    this->backgroundREC.setSize(sf::Vector2f(borderSize.width * 0.96, borderSize.height * 0.93));
    this->backgroundREC.setFillColor(sf::Color(51, 25, 0, 150));
    sf::FloatRect backgroundSize = this->backgroundREC.getGlobalBounds();
    this->backgroundREC.setOrigin(backgroundSize.width/2, backgroundSize.height/2);
}

void UIBox::draw(sf::RenderWindow &window) {
    window.draw(this->backgroundREC);
    window.draw(this->borderSP);
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