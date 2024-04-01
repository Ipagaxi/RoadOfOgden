#include "Animations/TextFadingManager.hpp"

TextFading::TextFading() {
    this->font.loadFromFile(RESOURCE_PATH "fonts/Avara-Bold.otf");
    this->text.setFont(this->font);
    this->text.setString("0");
    this->text.setCharacterSize(20);
    this->text.setFillColor(sf::Color::White);
    sf::FloatRect textRec = this->text.getGlobalBounds();
    this->text.setPosition(0., 0.);
    this->remainingVisibilty = 0;
}

TextFading::TextFading(std::string text, sf::Vector2f pos, sf::Color textColor, int textSize, sf::Font _font) {
    this->font = _font;
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(textSize);
    this->text.setFillColor(textColor);
    sf::FloatRect textRec = this->text.getGlobalBounds();
    this->text.setPosition(pos);
    this->remainingVisibilty = 0;
}

void TextFading::draw(sf::RenderWindow* gameWindow) {
    gameWindow->draw(this->text);
}

float TextFading::computeParabel(float value) {
    int f = 0.5 * (value*value);
    //std::cout << "F(" << std::to_string(value) << ") = " << std::to_string(f) << std::endl;
    return f;
}

void TextFading::setNewParabelPos() {
    sf::Vector2f oldPos = this->text.getPosition();
    float wholeDistanceX = this->pixelPerMillSec * this->millSecToLive;
    //std::cout << "Whole distance: " << std::to_string(wholeDistanceX) << std::endl;
    float currentDistanceX = this->pixelPerMillSec * this->pastMillSec;
    //std::cout << "current distance: " << std::to_string(currentDistanceX) << std::endl;
    float currentDistanceXRatio = static_cast<float>(this->pastMillSec) / this->millSecToLive;
    //std::cout << "current distance Ratio: " << std::to_string(currentDistanceXRatio) << std::endl;
    float functionShift = wholeDistanceX * 0.6;
    //std::cout << "Left Shift: " << std::to_string(functionShift) << std::endl;
    float parabelScale = 0.22;
    float newRelativePosY = this->computeParabel((currentDistanceX - functionShift) * parabelScale) - this->computeParabel((functionShift) * parabelScale);
    //std::cout << "New Relative Pos Y: " << std::to_string(newRelativePosY) << std::endl;
    float newRelativePosX = wholeDistanceX * (this->pastMillSec / static_cast<float>(this->millSecToLive));
    //std::cout << "New Relative Pos X: " << std::to_string(newRelativePosX) << std::endl;
    this->text.setPosition(this->initPosX + newRelativePosX, this->initPosY + newRelativePosY);
}

void TextFadingManager::updateAnimationState(GameStatus &gameStatus) {
    //std::cout << "Remaining Visibility: " << std::to_string(this->fadingText.remainingVisibilty) << std::endl;
    sf::Color oldColor = this->fadingText.text.getFillColor();
    sf::Vector2f oldPos = this->fadingText.text.getPosition();
    //std::cout << "Pos: " << std::to_string(oldPos.x) << ", " << std::to_string(oldPos.y) << std::endl;
    float pastRatio = gameStatus.elapsedTime.asMilliseconds() / static_cast<float>(this->fadingText.millSecToLive);
    int visRatio = int(255*pastRatio);
    this->fadingText.remainingVisibilty -= visRatio;
    this->fadingText.text.setFillColor(sf::Color(oldColor.r, oldColor.g, oldColor.b, this->fadingText.remainingVisibilty));
    float distanceToTravel = (this->fadingText.pixelPerMillSec * gameStatus.elapsedTime.asMilliseconds());
    switch (this->fadingText.animationPath) {
        case Left:
            this->fadingText.text.setPosition(oldPos.x - distanceToTravel, oldPos.y);
            break;
        case Right:
            this->fadingText.text.setPosition(oldPos.x + distanceToTravel, oldPos.y);
            break;
        case Up:
            this->fadingText.text.setPosition(oldPos.x, oldPos.y - distanceToTravel);
            break;
        case Down:
            this->fadingText.text.setPosition(oldPos.x, oldPos.y + distanceToTravel);
            break;
        case Parabel:
            this->fadingText.setNewParabelPos();
            break;
        default:
            break;
    }
    this->fadingText.pastMillSec += gameStatus.elapsedTime.asMilliseconds();
    if (this->fadingText.pastMillSec >= this->fadingText.millSecToLive) {
        //this->fadingText.pastMillSec = 0;
        this->isRunning = false;
    }
    //std::cout << "####################" << std::endl;
}

void TextFadingManager::run(sf::RenderWindow* gameWindow, GameStatus &gameStatus) {
    if (this->isRunning) {
        this->fadingText.draw(gameWindow);
        this->updateAnimationState(gameStatus);
    }
}

void TextFadingManager::startAnimation(std::string text, sf::Vector2f pos, sf::Color textColor, int textSize, AnimationPath _animationPath) {
    this->fadingText.text.setString(text);
    this->fadingText.text.setPosition(pos);
    this->fadingText.text.setFillColor(textColor);
    this->fadingText.text.setCharacterSize(textSize);
    this->fadingText.remainingVisibilty = 255;
    this->fadingText.animationPath = _animationPath;
    this->isRunning = true;
    if (_animationPath == AnimationPath::Parabel) {
        this->fadingText.pastMillSec = 0;
        this->fadingText.initPosY = pos.y;
        this->fadingText.initPosX = pos.x;
        //this->fadingText.scaleTimeToFctRange = this->fadingText.startingFunctionInput / static_cast<float>(this->fadingText.millSecToLive);
    }
}