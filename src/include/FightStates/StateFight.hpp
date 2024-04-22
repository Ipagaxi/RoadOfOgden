#ifndef FIGHTSTATE_HPP
#define FIGHTSTATE_HPP

#include "Game.hpp"
#include "FightEnv.hpp"
#include "FightStateEnum.hpp"

class StateFight {
  public:
    virtual FightStateEnum run(Game &game, FightEnv &fightEnv);
};

#endif