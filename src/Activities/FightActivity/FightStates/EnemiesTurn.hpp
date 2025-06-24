#ifndef ENEMIESTURN_HPP
#define ENEMIESTURN_HPP

#include <random>
#include "Activities/FightActivity/FightStates/FightState.hpp"
#include "Activities/FightActivity/FightStateEnum.hpp"
#include "Activities/FightActivity/FightActivityUI.hpp"
#include "System/GameUI.hpp"
#include "Activities/FightActivity/FightData.hpp"

class EnemiesTurn: public FightState {
  public:
    EnemiesTurn(FightData& fight_data);
    ~EnemiesTurn();
    FightStateEnum run() override;

  private:

    FightData& fight_data;
};

#endif