#include "GameState.hpp"

GameState::GameState(sf::RenderWindow &window, ActivityEnum activity) : renderEngine(&window) {

    gameWindow = &window;
    mouseMoved = false;
    mousePressed = false;
    mouseReleased = false;

    this->mainFont.loadFromFile(RESOURCE_PATH "fonts/Avara-Bold.otf");
}

void GameState::setCurrentActivity(std::unique_ptr<Activity> newActivity) {
    this->currentActivity = std::move(newActivity);
}