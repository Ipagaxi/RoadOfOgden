#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class GameState;

class Activity {
  public:
    virtual ~Activity();
    virtual void executeActivity(GameState &gameState);
};

#endif