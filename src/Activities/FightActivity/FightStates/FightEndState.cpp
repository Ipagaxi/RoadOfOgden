#include "FightEndState.hpp"

FightEndState::FightEndState(FightData& fight_data): fight_data(fight_data) {
  GameState& game_state = GameState::getInstance();
  int current_exp = game_state.player->get_experience();
  switch (fight_data.winning_party) {
      case WinningParty::ENEMY:
        this->turnChangeBanner.setNewLabel("Slayed!");
        game_state.player->set_experience(current_exp + (this->calculate_full_exp_reward() * 0.1));
        break;
      case WinningParty::PLAYER:
        this->turnChangeBanner.setNewLabel("You won");
        game_state.player->set_experience(current_exp + this->calculate_full_exp_reward());
        break;
      case WinningParty::NONE:
        this->turnChangeBanner.setNewLabel("Something wrong here?!");
        break;
      default:
        break;
    }
  
}

int FightEndState::calculate_full_exp_reward() {
  GameUI& game_ui = GameUI::getInstance();
  FightActivityUI& fight_activity_ui = game_ui.fight_activity_ui;
  Enemy& enemy = fight_activity_ui.enemyOverview->enemy;
  int enemy_level = enemy.get_level();
  int experience = enemy_level * enemy_level * enemy_level + 10;
  return experience;
}


FightStateEnum FightEndState::run() {
  GameUI& game_ui = GameUI::getInstance();
  FightActivityUI& fight_activity_ui = game_ui.fight_activity_ui;
  
  FightStateEnum currentFightState = FightStateEnum::FIGHT_END;
  this->turnChangeBanner.drawAnimation();
  
  if (!this->turnChangeBanner.runAnimation()) {
    switch (fight_data.winning_party) {
      case WinningParty::ENEMY:
        
        break;
      case WinningParty::PLAYER:
        
        break;
      case WinningParty::NONE:
        break;
      default:
        break;
    }
    SaveState::save_player_state();
  }
  return currentFightState;
}
