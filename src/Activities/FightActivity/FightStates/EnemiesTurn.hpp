#ifndef ENEMIESTURN_HPP
#define ENEMIESTURN_HPP

#include <random>
#include "Activities/FightActivity/FightStates/FightState.hpp"
#include "Activities/FightActivity/FightStateEnum.hpp"
#include "Activities/FightActivity/FightActivityUIObjects.hpp"

class EnemiesTurn: public FightState {
  public:
    ~EnemiesTurn();
    FightStateEnum run(FightActivityUIObjects &fightActivityUIObjects) override;

  private:
};

#endif