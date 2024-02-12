#include "UIElements/UIButton.hpp"

UIButton::UIButton() {}

UIButton::UIButton(std::string filePath, float x, float y) {
    std::cout << "UIButton constructor called" << std::endl;
    int sep_pos = filePath.find(".");
    std::string fileName = filePath.substr(0, sep_pos);
    std::string fileType = filePath.substr(sep_pos + 1);

    if(!this->basicTX.loadFromFile(RESOURCE_PATH + filePath)) {
        std::cout << "Error loading " << filePath << std::endl;
    }
    if(!this->clickedTX.loadFromFile(RESOURCE_PATH  + fileName + "_click." + fileType)) {
        std::cout << "Error loading " << fileName << "_click" << fileType << std::endl;
    }
    if(!this->hoveredTX.loadFromFile(RESOURCE_PATH + fileName + "_hover." + fileType)) {
        std::cout << "Error loading " << fileName << "_click" << fileType << std::endl;
    }

    this->buttonSP.setTexture(this->basicTX);
    this->buttonSP.setPosition(x, y);

    this->hovered = false;
    this->pressed = false;
}


void UIButton::hoverListener(GameState &gameState) {
    if (gameState.mouseMoved) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*(gameState.gameWindow));
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        if(this->buttonSP.getGlobalBounds().contains(mousePosF)) {
            this->buttonSP.setTexture(this->hoveredTX);
            this->hovered = true;
        } else {
            this->buttonSP.setTexture(this->basicTX);
            this->hovered = false;
        }
        gameState.mouseMoved = false;
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
    if (this->pressed && gameState.mouseReleased) {
        this->pressed = false;
        return this->buttonSP.getGlobalBounds().contains(gameState.releasedPos);
    }
    return false;
}