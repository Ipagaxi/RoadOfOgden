#ifndef TURNCHANGESTATE_HPP
#define TURNCHANGESTATE_HPP

#include "Activities/FightActivity/FightStates/FightState.hpp"
#include "Activities/FightActivity/FightStateEnum.hpp"
#include "Animations/IncomingBanner.hpp"
#include "System/Game.hpp"

class TurnChangeState: public FightState {
  public:
    TurnChangeState(FightActivityUIObjects &fightActivityUIObjects);
    ~TurnChangeState();
    FightStateEnum run(FightActivityUIObjects &fightActivityUIObjects) override;

  private:
    IncomingBanner turnChangeBanner;

};

#endif