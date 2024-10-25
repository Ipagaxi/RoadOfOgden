#ifndef ENEMIESTURN_HPP
#define ENEMIESTURN_HPP

#include <random>
#include "Activities/FightActivity/FightStates/FightState.hpp"
#include "Activities/FightActivity/FightStateEnum.hpp"
#include "Activities/FightActivity/FightActivityUI.hpp"
#include "System/GameUI.hpp"

class EnemiesTurn: public FightState {
  public:
    ~EnemiesTurn();
    FightStateEnum run() override;

  private:
};

#endif