#ifndef FIGHTSTATE_HPP
#define FIGHTSTATE_HPP

#include <iostream>

#include "Game.hpp"
#include "FightEnv.hpp"
#include "FightStateEnum.hpp"

class FightState {
  public:
    virtual ~FightState();
    virtual FightStateEnum run(Game &game, FightEnv &fightEnv);
};

#endif