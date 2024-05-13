#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>
#include <list>

#include "ObserverPattern/Observer.hpp"

struct RGB {
    int red = 0;
    int green = 0;
    int blue = 0;
};

class Actor: public Subject {
  public:
    std::string name;
    int health;
    int attackStrength;
    RGB defense;

    std::string picPath;

    Actor();

};

#endif