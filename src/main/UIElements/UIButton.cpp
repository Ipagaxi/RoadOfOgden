#include "UIElements/UIButton.hpp"

UIButton::UIButton() {}

UIButton::UIButton(std::string filePath, float x, float y) {
    std::string buttonsPath = RESOURCE_PATH "buttons/";
    std::cout << "UIButton constructor called" << std::endl;
    int sep_pos = filePath.find(".");
    std::string fileName = filePath.substr(0, sep_pos);
    std::string fileType = filePath.substr(sep_pos + 1);

    this->basicTX.loadFromFile(buttonsPath + filePath);
    this->clickedTX.loadFromFile(buttonsPath + fileName + "_click." + fileType);
    this->hoveredTX.loadFromFile(buttonsPath + fileName + "_hover." + fileType);

    this->buttonSP.setTexture(this->basicTX);
    this->buttonSP.setPosition(x, y);

    this->hovered = false;
    this->pressed = false;
}

bool UIButton::buttonContainsMouse(GameState &gameState) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*(gameState.gameWindow));
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    return this->buttonSP.getGlobalBounds().contains(mousePosF);
}


void UIButton::hoverListener(GameState &gameState) {
    if (gameState.mouseMoved) {
        if(this->buttonContainsMouse(gameState)) {
            this->buttonSP.setTexture(this->hoveredTX);
            this->hovered = true;
        } else {
            this->buttonSP.setTexture(this->basicTX);
            this->hovered = false;
        }
    } else if(this->hovered) {
        this->buttonSP.setTexture(this->hoveredTX);
    }
}

bool UIButton::clicked(GameState &gameState) {
    this->hoverListener(gameState);
    if (gameState.mousePressed && this->buttonSP.getGlobalBounds().contains(gameState.pressedPos)) {
        this->pressed = true;
    } else if (gameState.mousePressed){
        this->pressed = false;
    }
    if (this->pressed) {
        if (this->buttonContainsMouse(gameState)) {
            this->buttonSP.setTexture(this->clickedTX);
        }
        if (gameState.mouseReleased) {
            this->pressed = false;
            return this->buttonSP.getGlobalBounds().contains(gameState.releasedPos);
        }
    }
    return false;
}