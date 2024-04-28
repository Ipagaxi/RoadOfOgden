#ifndef ENEMIESTURN_HPP
#define ENEMIESTURN_HPP

#include <random>
#include "FightStates/FightState.hpp"
#include "FightStateEnum.hpp"

class EnemiesTurn: public FightState {
  public:
    ~EnemiesTurn();
    FightStateEnum run(Game &game, FightEnv &fightEnv) override;

  private:
};

#endif