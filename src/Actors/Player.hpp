#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Actors/Actor.hpp"

class Player: public Actor {
    private:

  public:
    int level;
    int experience;

      Player();
      Player(std::string name, int level, int experience, std::string picFilePath);


};

#endif