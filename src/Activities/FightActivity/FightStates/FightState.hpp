#ifndef FIGHTSTATE_HPP
#define FIGHTSTATE_HPP

#include <iostream>

#include "System/Game.hpp"
#include "Activities/FightActivity/FightActivityUI.hpp"
#include "Activities/FightActivity/FightStateEnum.hpp"

class FightState {
  public:
    virtual ~FightState();
    virtual FightStateEnum run();
};

#endif