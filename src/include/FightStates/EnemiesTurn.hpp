#ifndef ENEMIESTURN_HPP
#define ENEMIESTURN_HPP

#include "FightStates/FightState.hpp"
#include <random>

class EnemiesTurn: public FightState {
  public:
  void run(Game &game, FightEnv &fightEnv) override;

  private:
};

#endif