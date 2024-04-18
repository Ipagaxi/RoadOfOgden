#ifndef FIGHTSTATE_HPP
#define FIGHTSTATE_HPP

#include "Game.hpp"
#include "FightEnv.hpp"

class FightState {
  public:
    virtual void run(Game &game, FightEnv &fightEnv);
};

#endif