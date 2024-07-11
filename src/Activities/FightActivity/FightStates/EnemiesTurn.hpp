#ifndef ENEMIESTURN_HPP
#define ENEMIESTURN_HPP

#include <random>
#include "Activities/FightActivity/FightStates/FightState.hpp"
#include "Activities/FightActivity/FightStateEnum.hpp"

class EnemiesTurn: public FightState {
  public:
    ~EnemiesTurn();
    FightStateEnum run(FightEnv &fightEnv) override;

  private:
};

#endif