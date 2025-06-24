#ifndef FIGHTACTIVITY_HPP
#define FIGHTACTIVITY_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "Activities/Activity.hpp"
#include "System/Game.hpp"
#include "FightStates/PlayersTurn.hpp"
#include "FightStates/EnemiesTurn.hpp"
#include "FightStates/TurnChangeState.hpp"
#include "FightStates/FightEndState.hpp"
#include "FightStates/FightState.hpp"
#include "FightStateEnum.hpp"
#include "FightActivityUI.hpp"
#include "Global/Utility.hpp"
#include "Activities/FightActivity/UIEnemyOverview.hpp"
#include "Activities/FightActivity/UIPlayerOverview.hpp"
#include "System/GameState.hpp"
#include "Activities/FightActivity/FightData.hpp"

class FightActivity: public Activity {
  public:
    FightActivity();
    ~FightActivity();
  
    ActivityEnum executeActivity() override;
    void runCurrentState();

    FightData fight_data = FightData();

  private:

    FightStateEnum currentFightStateEnum = FightStateEnum::TURN_CHANGE;
    std::shared_ptr<Enemy> enemy;

    std::unique_ptr<FightState> currentFightState;

    Enemy initEnemy();
    void runPlayersTurn();
    void runEnemiesTurn();
    void runDefeat();
    void runVictory();
};

#endif