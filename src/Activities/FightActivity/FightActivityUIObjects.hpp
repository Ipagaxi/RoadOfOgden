#ifndef FIGHTEVENTS_HPP
#define FIGHTEVENTS_HPP

#include <SFML/Graphics.hpp>
#include "UIElements/UIStats.hpp"
#include "Activities/FightActivity/UIEnemyOverview.hpp"
#include "Activities/FightActivity/UIPlayerOverview.hpp"
#include "Animations/TextFadingManager.hpp"
#include "Animations/IncomingBanner.hpp"
#include "System/Game.hpp"

/*
 * This class has the UI components and therefore provides these to the different fight phases
 * Not an ideal solution
 */

class FightActivityUIObjects {
  public:
    FightActivityUIObjects();

    sf::Texture backgroundTX;
    sf::Sprite backgroundSP;
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