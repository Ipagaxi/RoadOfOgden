#include "UIElements/UIButton.hpp"

void UIButton::init(std::string filePath) {
    std::string buttonsPath = RESOURCE_PATH "buttons/";
    int sep_pos = filePath.find(".");
    std::string fileName = filePath.substr(0, sep_pos);
    std::string fileType = filePath.substr(sep_pos + 1);

    this->basicTX.loadFromFile(buttonsPath + filePath);
    this->clickedTX.loadFromFile(buttonsPath + fileName + "_click." + fileType);
    this->hoveredTX.loadFromFile(buttonsPath + fileName + "_hover." + fileType);
    this->buttonSP.setTexture(this->basicTX);

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

sf::FloatRect UIButton::getSize() {
    return this->buttonSP.getGlobalBounds();
}

void UIButton::scale(float x, float y) {
    this->buttonSP.scale(sf::Vector2f(x, y));
    sf::FloatRect buttonSize = this->getSize();
    this->label.setCharacterSize(buttonSize.height * 0.5);
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

sf::Vector2f UIButton::getPosition() {
    return this->buttonSP.getPosition();
}


bool UIButton::buttonContainsMouse(sf::RenderWindow &gameWindow) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    return this->buttonSP.getGlobalBounds().contains(mousePosF);
}


void UIButton::hoverListener(sf::RenderWindow &gameWindow, GameEvents &gameEvents) {
    if (gameEvents.mouseMoved) {
        if(this->buttonContainsMouse(gameWindow)) {
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

bool UIButton::clickListener(sf::RenderWindow &gameWindow, GameEvents &gameEvents) {
    this->hoverListener(gameWindow, gameEvents);
    if (gameEvents.mousePressed && this->buttonSP.getGlobalBounds().contains(gameEvents.pressedPos)) {
        this->pressSound.play();
        this->pressed = true;
    } else if (gameEvents.mousePressed){
        this->pressed = false;
    }
    if (this->pressed) {
        if (this->buttonContainsMouse(gameWindow)) {
            this->buttonSP.setTexture(this->clickedTX);
        }
        if (gameEvents.mouseReleased) {
            this->pressed = false;
            if (this->buttonSP.getGlobalBounds().contains(gameEvents.releasedPos)) {
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