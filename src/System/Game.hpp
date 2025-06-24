#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>

#include "Activities/ActivityEnum.hpp"
#include "Global/Utility.hpp"
#include "Actors/Player.hpp"
#include "System/GameEvents.hpp"
#include "System/RenderEngine.hpp"
#include "System/GameStatus.hpp"

class Game {
  public:
    sf::Font mainFont;
    GameEvents gameEvents;
    GameStatus gameStatus;
    //sf::RenderWindow& gameWindow;

    static Game& getInstance();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
  private:
    Game();
    ~Game();
    static Game* instance;
};

#endif