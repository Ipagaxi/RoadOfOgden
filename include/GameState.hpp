#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "ActivityEnum.hpp"
#include "Activities/Activity.hpp"

class GameState {
  public:
    std::unique_ptr<Activity> currentActivity;
    int counter;

    sf::RenderWindow* gameWindow;

    GameState(sf::RenderWindow &window, ActivityEnum activity);

    void setCurrentActivity(std::unique_ptr<Activity> newActivity);
};

#endif