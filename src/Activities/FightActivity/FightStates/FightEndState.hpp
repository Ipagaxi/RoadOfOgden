#ifndef FIGHTENDSTATE_HPP
#define FIGHTENDSTATE_HPP

#include "Activities/FightActivity/FightStates/FightState.hpp"
#include <System/GameUI.hpp>
#include "Animations/IncomingBanner.hpp"

class FightEndState: public FightState {
  public:
    FightEndState();
    FightStateEnum run() override;
  private:
    IncomingBanner turnChangeBanner = IncomingBanner("Fight End");
};

#endif