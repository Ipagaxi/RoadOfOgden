#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Actors/Actor.hpp"

class Player: public Actor {
    private:

  public:
      Player();
      Player(std::string name, int health, int attackStrength, RGB defense, std::string picFilePath);

      void notify(int newValue) const override;
};

#endif