#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

#include "ActivityEnum.hpp"
#include "Activities/Activity.hpp"
#include "Defines.hpp"
#include "Actors/Player.hpp"
#include "GameEvents.hpp"
#include "RenderEngine.hpp"
#include "GameStatus.hpp"

class GameState {
  public:
    std::unique_ptr<Activity> currentActivity;

    sf::Font mainFont;
    //sf::Music backgroundMusic;
    sf::RenderWindow* gameWindow; // Becomes deprecated
    GameEvents gameEvents;
    RenderEngine renderEngine;
    sf::Time elapsedTime;
    GameStatus gameStatus;

    Player player = Player("Ipagaxi", 100, 12, {100, 100, 100}, "default_actor_quer.png");

    GameState(sf::RenderWindow &window, ActivityEnum activity);
};

#endif