#include "UIElements/UIColorBox.hpp"

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

sf::Vector2u UIColorBox::clickListener(GameState &gameState) {
    if (gameState.mousePressed && this->colorSP.getGlobalBounds().contains(gameState.pressedPos)) {
        this->pressed = true;
    } else if (gameState.mousePressed){
        this->pressed = false;
    }
    if (this->pressed) {
        if (gameState.mouseReleased) {
            this->pressed = false;
            if (this->colorSP.getGlobalBounds().contains(gameState.releasedPos)) {
                return sf::Vector2u(int(gameState.releasedPos.x), int(gameState.releasedPos.y));
            }
        }
    }
    return sf::Vector2u(0, 0);
}

void UIColorBox::updateClickedPixelColor(GameState &gameState, sf::Color &color_out) {
    sf::Vector2u getClickPos = this->clickListener(gameState);
    color_out = this->colorBoxIMG.getPixel(getClickPos.x, getClickPos.y);
}