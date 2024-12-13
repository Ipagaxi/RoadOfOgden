#include "FightEndState.hpp"

FightEndState::FightEndState() {
  std::cout << "Init Fight End State" << std::endl;
}


FightStateEnum FightEndState::run() {
  GameUI& game_ui = GameUI::getInstance();
  FightActivityUI &fight_activity_ui = game_ui.fight_activity_ui;
  FightStateEnum currentFightState = FightStateEnum::FIGHT_END;
  this->turnChangeBanner.drawAnimation();
  if (!this->turnChangeBanner.runAnimation()) {
    // Show fight results
  }
  return currentFightState;
}
