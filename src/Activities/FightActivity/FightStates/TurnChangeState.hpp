#ifndef TURNCHANGESTATE_HPP
#define TURNCHANGESTATE_HPP

#include "Activities/FightActivity/FightStates/FightState.hpp"
#include "Activities/FightActivity/FightStateEnum.hpp"
#include "Animations/IncomingBanner.hpp"
#include "System/GameUI.hpp"
#include "System/Game.hpp"

class TurnChangeState: public FightState {
  public:
    TurnChangeState();
    ~TurnChangeState();
    FightStateEnum run() override;

  private:
    IncomingBanner turnChangeBanner;

};

#endif