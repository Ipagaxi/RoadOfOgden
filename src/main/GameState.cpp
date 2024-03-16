#include "GameState.hpp"

GameState::GameState(sf::RenderWindow &window, ActivityEnum activity) {
    gameWindow = &window;
    mouseMoved = false;
    mousePressed = false;
    mouseReleased = false;

    this->mainFont.loadFromFile(RESOURCE_PATH "fonts/Avara-Bold.otf");
}

void GameState::setCurrentActivity(std::unique_ptr<Activity> newActivity) {
    std::cout << "set activity called" << std::endl;
    this->currentActivity.reset();
    this->currentActivity = std::move(newActivity);
}