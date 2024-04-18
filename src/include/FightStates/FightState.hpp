#ifndef FIGHTSTATE_HPP
#define FIGHTSTATE_HPP

#include "Game.hpp"

class FightState {
  public:
    virtual void run(Game &game);
};

#endif