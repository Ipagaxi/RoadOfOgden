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

sf::Vector2u UIBox::getSize() {
    sf::FloatRect borderRect = this->borderSP.getGlobalBounds();
    return sf::Vector2u(borderRect.width, borderRect.height);
}
        
void UIBox::setPosition(float x, float y) {
    this->borderSP.setPosition(x, y);
    sf::Vector2u borderSize = this->getSize();
    this->backgroundREC.setPosition(x + (borderSize.x/2), y + (borderSize.y/2));
}

sf::Vector2f UIBox::getPosition() {
    return this->borderSP.getPosition();
}

void UIBox::scale(float x, float y) {
    this->borderSP.scale(sf::Vector2f(x, y));
    this->backgroundREC.scale(sf::Vector2f(x, y));
}