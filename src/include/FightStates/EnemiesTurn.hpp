#ifndef ENEMIESTURN_HPP
#define ENEMIESTURN_HPP

#include <random>
#include "FightStates/FightState.hpp"
#include "FightStateEnum.hpp"

class EnemiesTurn: public FightState {
  public:
    ~EnemiesTurn();
    FightStateEnum run(FightEnv &fightEnv) override;

  private:
};

#endif