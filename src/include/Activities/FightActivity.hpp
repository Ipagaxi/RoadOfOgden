#ifndef FIGHTACTIVITY_HPP
#define FIGHTACTIVITY_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <random>

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

class FightActivity: public Activity {
  public:
    FightActivity(Game &game);
    ~FightActivity();
  
    ActivityEnum executeActivity(Game &game) override;
    void runFight(Game &game);

  private:
    sf::Texture backgroundTX;
    sf::Sprite backgroundSP;
    UIButton exitButton = UIButton("buttonClose/buttonClose.png");
    UIStats playerStatsBox;
    UIEnemyOverview enemyOverview;
    UIPlayerOverview playerOverview;
    TextFadingManager textFadingManager;
    sf::Texture playersTurnTX;
    sf::Texture enemiesTurnTX;
    sf::Sprite turnSP;
    IncomingBanner turnChangeBanner;
    sf::Music backgroundMusic;

    sf::Color pickedColor;
    int maxMultiplier = 2;
    int isPlayersTurn;
    bool enemyDamageCalculated = false;
    bool turnIsChanging = true;

    Enemy initEnemy();
    void runPlayersTurn(Game &game);
    void runEnemiesTurn(Game &game);
    void runDefeat(Game &game);
    void runVictory(Game &game);

    // Compute damage multiplier
    float mapInInterval(float value);
    float calculateSingleMultPart(Color color);
    float calculateAttackMult();
    // Metrics in file DamageMultMetrics.cpp
    float counterColorMetric(Color color);
    float tugOfWarMetric(Color color);
};

#endif