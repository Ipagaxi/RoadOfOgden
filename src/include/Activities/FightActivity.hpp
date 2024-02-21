#ifndef FIGHTACTIVITY_HPP
#define FIGHTACTIVITY_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Activities/Activity.hpp"
#include "GameState.hpp"
#include "ActivityEnum.hpp"
#include "Activities/MenuActivity.hpp"
#include "UIElements/UIColorBox.hpp"
#include "UIElements/UIButton.hpp"
#include "UIElements/UIBox.hpp"
#include "Defines.hpp"
#include "PerlinNoise.hpp"

class FightActivity: public Activity {
  private:
    std::string nameEnemy = "Enemy";

    sf::Texture backgroundTX;
    sf::Sprite backgroundSP;
    UIButton exitButton = UIButton("buttonClose/buttonClose.png");

    UIColorBox colorBox = UIColorBox("colorPIC_gen.png", "borderMetal.png");
    sf::Text colorText;
    sf::Color pickedColor;

    UIBox characterStatsBox = UIBox();
    sf::Text playerName;
    sf::Text playerHealthLabel;
    sf::Text playerHealthValue;


  public:
    FightActivity(GameState &gameState);
  
    void executeActivity(GameState &gameState) override;
    void runFight(GameState &gameState);
};

#endif