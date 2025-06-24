#ifndef FIGHTACTIVITYUI_HPP
#define FIGHTACTIVITYUI_HPP

#include <memory>
#include <Animations/TextFadingManager.hpp>
#include <SFML/Graphics.hpp>

#include "UIEnemyOverview.hpp"
#include "UIPlayerOverview.hpp"
#include "SFML/Audio/Music.hpp"



/*
 * This class has the UI components and therefore provides these to the different fight phases
 * Not an ideal solution
 */

class FightActivityUI {
  public:
    FightActivityUI();

    std::unique_ptr<UIEnemyOverview> enemyOverview;
    std::unique_ptr<UIPlayerOverview> playerOverview;
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