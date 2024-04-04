#ifndef ACTIVITY_HPP
#define ACTIVITY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "GameEvents.hpp"
#include "ActivityEnum.hpp"

class Game;

class Activity {
  public:
    virtual ~Activity();
    virtual ActivityEnum executeActivity(Game &game);
};

#endif