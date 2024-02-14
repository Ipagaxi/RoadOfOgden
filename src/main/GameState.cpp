#include "GameState.hpp"

GameState::GameState(sf::RenderWindow &window, ActivityEnum activity) {
    gameWindow = &window;
    mouseMoved = false;
    mousePressed = false;
    mouseReleased = false;
}

void GameState::setCurrentActivity(std::unique_ptr<Activity> newActivity) {
    currentActivity = std::move(newActivity);
}