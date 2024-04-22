#ifndef STATETURNCHANGE_HPP
#define STATETURNCHANGE_HPP

#include "StateFight.hpp"
#include "FightStateEnum.hpp"

class StateTurnChange: public StateFight {
  public:
    FightStateEnum run(Game &game, FightEnv &fightEnv) override;
};

#endif