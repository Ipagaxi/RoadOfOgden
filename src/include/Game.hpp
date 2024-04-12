#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

#include "ActivityEnum.hpp"
//#include "Activities/Activity.hpp"
#include "Defines.hpp"
#include "Actors/Player.hpp"
#include "GameEvents.hpp"
#include "RenderEngine.hpp"
#include "GameStatus.hpp"

class Game {
  public:
    sf::Font mainFont;
    //sf::Music backgroundMusic;
    GameEvents gameEvents;
    RenderEngine renderEngine;
    GameStatus gameStatus;

    Player player = Player("Ipagaxi", 100, 12, {100, 100, 100}, "default_actor_quer.png");

    Game(sf::RenderWindow &window, ActivityEnum activity);
};

#endif