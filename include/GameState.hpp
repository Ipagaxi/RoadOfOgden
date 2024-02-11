#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "ActivityEnum.hpp"
#include "Activities/Activity.hpp"
#include "Defines.hpp"

class GameState {
  public:
    std::unique_ptr<Activity> currentActivity;
    int counter;
    bool mouseMoved;
    bool mousePressed;
    bool mouseReleased;

    sf::Vector2f pressedPos;
    sf::Vector2f releasedPos;

    sf::Texture buttonTX;

    sf::RenderWindow* gameWindow;

    GameState(sf::RenderWindow &window, ActivityEnum activity);

    void setCurrentActivity(std::unique_ptr<Activity> newActivity);
};

#endif