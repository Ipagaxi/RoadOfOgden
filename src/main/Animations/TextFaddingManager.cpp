#include "Animations/TextFaddingManager.hpp"

TextFadding::TextFadding() {
    this->font.loadFromFile(RESOURCE_PATH "fonts/Avara-Bold.otf");
    this->text.setFont(this->font);
    this->text.setString("0");
    this->text.setCharacterSize(20);
    this->text.setFillColor(sf::Color::White);
    sf::FloatRect textRec = this->text.getGlobalBounds();
    this->text.setPosition(0., 0.);
    this->pixelPerMillSec = 0.1;
    this->remainingVisibilty = 255;
}

TextFadding::TextFadding(std::string text, sf::Vector2f pos, sf::Color textColor, int textSize, sf::Font _font, float _pixelPerMilSec) {
    this->font = _font;
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(textSize);
    this->text.setFillColor(textColor);
    sf::FloatRect textRec = this->text.getGlobalBounds();
    this->text.setPosition(pos);
    this->pixelPerMillSec = _pixelPerMilSec;
    this->remainingVisibilty = 255;
}

void TextFadding::draw(GameState &gameState) {
    gameState.gameWindow->draw(this->text);
}

void TextFaddingManager::updateAnimationState(GameState &gameState, TextFadding &faddingText) {
    std::cout << "Remaining Visibility: " << std::to_string(faddingText.remainingVisibilty) << std::endl;
    sf::Color oldColor = faddingText.text.getFillColor();
    sf::Vector2f oldPos = faddingText.text.getPosition();
    std::cout << "Old Pos: " << std::to_string(oldPos.x) << ", " << std::to_string(oldPos.y) << std::endl;
    float pastRatio = gameState.elapsedTime.asMilliseconds() / static_cast<float>(faddingText.millSecToLive);
    int visRatio = int(255*pastRatio);
    faddingText.remainingVisibilty -= visRatio;
    faddingText.text.setFillColor(sf::Color(oldColor.r, oldColor.g, oldColor.b, faddingText.remainingVisibilty));
    switch (faddingText.animationPath) {
        case Left:
            faddingText.text.setPosition(oldPos.x - (faddingText.pixelPerMillSec * gameState.elapsedTime.asMilliseconds()), oldPos.y);
            break;
        case Right:
            faddingText.text.setPosition(oldPos.x + (faddingText.pixelPerMillSec * gameState.elapsedTime.asMilliseconds()), oldPos.y);
            break;
        default:
            break;
    }
    sf::Vector2f newPos = faddingText.text.getPosition();
    std::cout << "New Pos. " << std::to_string(newPos.x) << ", " << std::to_string(newPos.y) << std::endl;
    
}

void TextFaddingManager::run(GameState &gameState) {
    if (faddingText.remainingVisibilty > 0) {
        this->faddingText.draw(gameState);
        this->updateAnimationState(gameState, this->faddingText);
    }
}

void TextFaddingManager::startAnimation(GameState &gameState, std::string text, sf::Vector2f pos, sf::Color textColor, int textSize, float pixelPerMillSec) {
    this->faddingText.text.setString(text);
    this->faddingText.text.setPosition(pos);
    this->faddingText.text.setFillColor(textColor);
    this->faddingText.text.setCharacterSize(textSize);
    this->faddingText.pixelPerMillSec = pixelPerMillSec;
    this->faddingText.remainingVisibilty = 255;
}