#ifndef FIGHTEVENTS_HPP
#define FIGHTEVENTS_HPP

#include <SFML/Graphics.hpp>
#include "UIComponents/UIStats.hpp"
#include "UI_Objects/UIEnemyOverview.hpp"
#include "UI_Objects/UIPlayerOverview.hpp"
#include "Animations/TextFadingManager.hpp"
#include "Animations/IncomingBanner.hpp"
#include "Game.hpp"

class FightEnv {
  public:
    FightEnv(Game &game);

    sf::Texture backgroundTX;
    sf::Sprite backgroundSP;
    UIStats playerStatsBox;
    UIEnemyOverview enemyOverview;
    UIPlayerOverview playerOverview;
    TextFadingManager textFadingManager;
    sf::Texture playersTurnTX;
    sf::Texture enemiesTurnTX;
    sf::Sprite turnSP;
    sf::Music backgroundMusic;

    sf::Color pickedColor;
    int maxMultiplier = 2;
    int isPlayersTurn;
    bool enemyDamageCalculated = false;

};

#endif