#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "GameEvents.hpp"
#include "ActivityEnum.hpp"

class GameState;

class Activity {
  public:
    virtual ~Activity();
    virtual ActivityEnum executeActivity(GameState &game);
};

#endif