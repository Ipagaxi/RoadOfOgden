#ifndef FIGHTACTIVITY_HPP
#define FIGHTACTIVITY_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "Activities/Activity.hpp"
#include "ActivityEnum.hpp"
#include "Animations/TextFadingManager.hpp"
#include "Animations/IncomingBanner.hpp"
#include "UIElements/UIStats.hpp"
#include "UIObjects/UIEnemyOverview.hpp"
#include "UIObjects/UIPlayerOverview.hpp"
#include "UIElements/UIColorPicker.hpp"
#include "UIElements/UIButton.hpp"
#include "UIElements/UIBox.hpp"
#include "Actors/Player.hpp"
#include "PerlinNoise.hpp"
#include "Game.hpp"
#include "Defines.hpp"
#include "Actors/Enemy.hpp"
#include "Color.hpp"
#include "FightEnv.hpp"
#include "FightStates/PlayersTurn.hpp"
#include "FightStates/EnemiesTurn.hpp"
#include "FightStates/TurnChangeState.hpp"
#include "FightStates/FightState.hpp"
#include "FightStateEnum.hpp"

class FightActivity: public Activity {
  public:
    FightActivity();
    ~FightActivity();
  
    ActivityEnum executeActivity() override;
    void runCurrentState(Game &game);

  private:
    FightEnv fightEnv;
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