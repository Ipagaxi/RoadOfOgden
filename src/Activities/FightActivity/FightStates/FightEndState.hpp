#ifndef FIGHTENDSTATE_HPP
#define FIGHTENDSTATE_HPP

#include "Activities/FightActivity/FightStates/FightState.hpp"
#include <System/GameUI.hpp>
#include "Animations/IncomingBanner.hpp"
#include "Activities/FightActivity/FightData.hpp"
#include "System/GameState.hpp"
#include "Global/Save.hpp"

class FightEndState: public FightState {
  public:
    FightEndState(FightData& fight_data);
    FightStateEnum run() override;
  private:
    IncomingBanner turnChangeBanner = IncomingBanner("Fight End");
    FightData& fight_data;

    int calculate_full_exp_reward();
};

#endif