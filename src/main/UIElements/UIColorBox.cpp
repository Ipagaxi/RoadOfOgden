#include "UIElements/UIColorBox.hpp"

void UIColorBox::draw(sf::RenderWindow &window) {
    window.draw(this->colorSP);
    window.draw(this->borderSP);
}

void UIColorBox::setPosition(float x, float y) {
    this->borderSP.setPosition(x, y);
    sf::Vector2u borderSize = this->getSize();
    this->colorSP.setPosition(x + (borderSize.x/2), y + (borderSize.y/2));
}

sf::Vector2u UIColorBox::getSize() {
    sf::FloatRect size = this->borderSP.getGlobalBounds();
    return sf::Vector2u(size.width, size.height);
}

UIColorBox::UIColorBox(std::string imagePath, std::string borderPath) {
    this->colorTX.loadFromFile(RESOURCE_PATH "color_textures/" + imagePath);
    this->colorSP.setTexture(this->colorTX);
    this->borderTX.loadFromFile(RESOURCE_PATH "borders/" + borderPath);
    this->borderSP.setTexture(this->borderTX);

    sf::FloatRect colorRect = this->colorSP.getGlobalBounds();
    this->colorSP.setOrigin(colorRect.width/2, colorRect.height/2);

    // For a save small overlap
    this->borderSP.scale(0.97, 0.97);

    this->colorBoxIMG.loadFromFile(RESOURCE_PATH "color_textures/" + imagePath);
}