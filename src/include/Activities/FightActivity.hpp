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
#include "UIComponents/UIStats.hpp"
#include "UI_Objects/UIEnemyOverview.hpp"
#include "UI_Objects/UIPlayerOverview.hpp"
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
#include "FightStates/StateTurnChange.hpp"
#include "FightStateEnum.hpp"

class FightActivity: public Activity {
  public:
    FightActivity(Game &game);
    ~FightActivity();
  
    ActivityEnum executeActivity(Game &game) override;
    void runCurrentState(Game &game);

  private:
    FightEnv fightEnv;
    FightStateEnum currentFightState = FightStateEnum::TURN_CHANGE;

    PlayersTurn playersTurn;
    EnemiesTurn enemiesTurn;
    StateTurnChange stateTurnChange;

    Enemy initEnemy();
    void runPlayersTurn(Game &game);
    void runEnemiesTurn(Game &game);
    void runDefeat(Game &game);
    void runVictory(Game &game);
};

#endif