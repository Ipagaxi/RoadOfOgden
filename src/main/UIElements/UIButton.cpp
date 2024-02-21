#include "UIElements/UIButton.hpp"

void UIButton::init(std::string filePath) {
    std::string buttonsPath = RESOURCE_PATH "buttons/";
    int sep_pos = filePath.find(".");
    std::string fileName = filePath.substr(0, sep_pos);
    std::string fileType = filePath.substr(sep_pos + 1);

    this->basicTX.loadFromFile(buttonsPath + filePath);
    this->clickedTX.loadFromFile(buttonsPath + fileName + "_click." + fileType);
    this->hoveredTX.loadFromFile(buttonsPath + fileName + "_hover." + fileType);

    this->hovered = false;
    this->pressed = false;

    this->pressSoundBuffer.loadFromFile(RESOURCE_PATH "test_sounds/tick.wav");
    //this->pressSoundBuffer.loadFromFile(RESOURCE_PATH "test_sounds/buttonAlpha2.wav");
    this->pressSound.setBuffer(this->pressSoundBuffer);
    //this->releaseSound.setBuffer(this->releaseSoundBuffer);
}

UIButton::UIButton() {}

UIButton::UIButton(std::string filePath) {
    this->init(filePath);
}

UIButton::UIButton(std::string labelText, std::string filePath) {
    this->init(filePath);

    sf::Vector2u buttonSize = this->basicTX.getSize();
    this->font.loadFromFile(RESOURCE_PATH "fonts/Avara-Bold.otf");
    this->label.setFont(this->font);
    this->label.setString(labelText);
    this->label.setCharacterSize(buttonSize.y * 0.5);
    this->label.setFillColor(sf::Color::Black);
}

sf::Vector2u UIButton::getSize() {
    sf::FloatRect size = this->buttonSP.getGlobalBounds();
    return sf::Vector2u(size.width, size.height);
}

void UIButton::scale(float x, float y) {
    this->buttonSP.scale(sf::Vector2f(x, y));
    sf::Vector2u buttonSize = this->getSize();
    this->label.setCharacterSize(buttonSize.y * 0.5);
}

void UIButton::draw(sf::RenderWindow &window) {
    window.draw(this->buttonSP);
    window.draw(this->label);
}

void UIButton::setPosition(float x, float y) {
    this->buttonSP.setPosition(x, y);

    sf::Vector2u buttonSize = this->basicTX.getSize();
    sf::Vector2f buttonPos = this->buttonSP.getPosition();
    sf::FloatRect textRect = this->label.getLocalBounds();
    this->label.setOrigin(textRect.width/2, textRect.height/2);
    this->label.setPosition(buttonPos.x + buttonSize.x/2, buttonPos.y + buttonSize.y/2);
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

bool UIButton::clickListener(GameState &gameState) {
    this->hoverListener(gameState);
    if (gameState.mousePressed && this->buttonSP.getGlobalBounds().contains(gameState.pressedPos)) {
        this->pressSound.play();
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
            if (this->buttonSP.getGlobalBounds().contains(gameState.releasedPos)) {
                // Sound is attached to button. Therefore, stops when activity changes
                //this->releaseSound.play();
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}