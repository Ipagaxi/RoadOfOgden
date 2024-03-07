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
#include "UIComponents/UIStats.hpp"
#include "UIEnemyOverview.hpp"
#include "UIPlayerOverview.hpp"
#include "Activities/MenuActivity.hpp"
#include "UIElements/UIColorPicker.hpp"
#include "UIElements/UIButton.hpp"
#include "UIElements/UIBox.hpp"
#include "Actors/Player.hpp"
#include "PerlinNoise.hpp"
#include "GameState.hpp"
#include "Defines.hpp"
#include "Actors/Enemy.hpp"

enum Color {
  RED,
  GREEN,
  BLUE
};

class FightActivity: public Activity {
  public:
    FightActivity(GameState &gameState);
  
    void executeActivity(GameState &gameState) override;
    void runFight(GameState &gameState);

  private:
    sf::Texture backgroundTX;
    sf::Sprite backgroundSP;
    UIButton exitButton = UIButton("buttonClose/buttonClose.png");
    UIStats playerStatsBox;
    UIEnemyOverview enemyOverview;
    UIPlayerOverview playerOverview;

    sf::Color pickedColor;
    int maxMultiplier = 2;

    Enemy initEnemy();

    float mapInInterval(float value);
    float counterColorMetric(Color color);
    float tugOfWarMetric(Color color);
    float calculateSingleMultPart(Color color);
    float calculateAttackMult();
};

#endif