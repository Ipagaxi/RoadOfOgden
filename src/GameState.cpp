#include "GameState.hpp"

GameState::GameState(sf::RenderWindow &window, ActivityEnum activity) {
    gameWindow = &window;
    counter = 0;
    mouseMoved = false;
    mousePressed = false;
    mouseReleased = false;
    if(!buttonTX.loadFromFile(RESOURCE_PATH "button1.png")) {
        std::cout << "Error loading button1.png" << std::endl;
    }
}

void GameState::setCurrentActivity(std::unique_ptr<Activity> newActivity) {
    currentActivity = std::move(newActivity);
}