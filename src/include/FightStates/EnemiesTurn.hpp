#ifndef ENEMIESTURN_HPP
#define ENEMIESTURN_HPP

#include <random>
#include "FightStates/StateFight.hpp"
#include "FightStateEnum.hpp"

class EnemiesTurn: public StateFight {
  public:
   FightStateEnum run(Game &game, FightEnv &fightEnv) override;

  private:
};

#endif