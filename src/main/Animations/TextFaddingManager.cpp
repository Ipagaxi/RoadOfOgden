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
    this->remainingVisibilty = 0;
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
    this->remainingVisibilty = 0;
}

void TextFadding::draw(GameState &gameState) {
    gameState.gameWindow->draw(this->text);
}

float TextFadding::computeParabel(float value) {
    int f = 0.5 * (value*value);
    std::cout << "F(" << std::to_string(value) << ") = " << std::to_string(f) << std::endl;
    return f;
}

void TextFadding::setNewParabelPos() {
    sf::Vector2f oldPos = this->text.getPosition();
    float wholeDistanceX = this->pixelPerMillSec * this->millSecToLive;
    std::cout << "Whole distance: " << std::to_string(wholeDistanceX) << std::endl;
    float currentDistanceX = this->pixelPerMillSec * this->pastMillSec;
    std::cout << "current distance: " << std::to_string(currentDistanceX) << std::endl;
    float currentDistanceXRatio = static_cast<float>(this->pastMillSec) / this->millSecToLive;
    std::cout << "current distance Ratio: " << std::to_string(currentDistanceXRatio) << std::endl;
    float functionShift = wholeDistanceX * 0.6;
    std::cout << "Left Shift: " << std::to_string(functionShift) << std::endl;
    float parabelScale = 0.22;
    float newRelativePosY = this->computeParabel((currentDistanceX - functionShift) * parabelScale) - this->computeParabel((functionShift) * parabelScale);
    std::cout << "New Relative Pos Y: " << std::to_string(newRelativePosY) << std::endl;
    float newRelativePosX = wholeDistanceX * (this->pastMillSec / static_cast<float>(this->millSecToLive));
    std::cout << "New Relative Pos X: " << std::to_string(newRelativePosX) << std::endl;
    this->text.setPosition(this->initPosX + newRelativePosX, this->initPosY + newRelativePosY);
}

void TextFaddingManager::updateAnimationState(GameState &gameState) {
    std::cout << "Remaining Visibility: " << std::to_string(this->faddingText.remainingVisibilty) << std::endl;
    sf::Color oldColor = this->faddingText.text.getFillColor();
    sf::Vector2f oldPos = this->faddingText.text.getPosition();
    std::cout << "Pos: " << std::to_string(oldPos.x) << ", " << std::to_string(oldPos.y) << std::endl;
    float pastRatio = gameState.elapsedTime.asMilliseconds() / static_cast<float>(this->faddingText.millSecToLive);
    int visRatio = int(255*pastRatio);
    this->faddingText.remainingVisibilty -= visRatio;
    this->faddingText.text.setFillColor(sf::Color(oldColor.r, oldColor.g, oldColor.b, this->faddingText.remainingVisibilty));
    float distanceToTravel = (this->faddingText.pixelPerMillSec * gameState.elapsedTime.asMilliseconds());
    switch (this->faddingText.animationPath) {
        case Left:
            this->faddingText.text.setPosition(oldPos.x - distanceToTravel, oldPos.y);
            break;
        case Right:
            this->faddingText.text.setPosition(oldPos.x + distanceToTravel, oldPos.y);
            break;
        case Up:
            this->faddingText.text.setPosition(oldPos.x, oldPos.y - distanceToTravel);
            break;
        case Down:
            this->faddingText.text.setPosition(oldPos.x, oldPos.y + distanceToTravel);
            break;
        case Parabel:
            this->faddingText.setNewParabelPos();
            break;
        default:
            break;
    }
    this->faddingText.pastMillSec += gameState.elapsedTime.asMilliseconds();
    std::cout << "####################" << std::endl;
}

void TextFaddingManager::run(GameState &gameState) {
    if (this->faddingText.pastMillSec < this->faddingText.millSecToLive) {
        this->faddingText.draw(gameState);
        this->updateAnimationState(gameState);
    }
}

void TextFaddingManager::startAnimation(GameState &gameState, std::string text, sf::Vector2f pos, sf::Color textColor, int textSize, float pixelPerMillSec, AnimationPath _animationPath) {
    this->faddingText.text.setString(text);
    this->faddingText.text.setPosition(pos);
    this->faddingText.text.setFillColor(textColor);
    this->faddingText.text.setCharacterSize(textSize);
    this->faddingText.pixelPerMillSec = pixelPerMillSec;
    this->faddingText.remainingVisibilty = 255;
    this->faddingText.animationPath = _animationPath;
    if (_animationPath == AnimationPath::Parabel) {
        this->faddingText.pastMillSec = 0;
        this->faddingText.initPosY = pos.y;
        this->faddingText.initPosX = pos.x;
        //this->faddingText.scaleTimeToFctRange = this->faddingText.startingFunctionInput / static_cast<float>(this->faddingText.millSecToLive);
    }
}