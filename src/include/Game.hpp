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
    GameEvents gameEvents;
    GameStatus gameStatus;
    sf::RenderWindow& gameWindow;

    std::shared_ptr<Player> player = std::make_shared<Player>(Player("Ipagaxi", 100, 12, {100, 100, 100}, "default_actor_quer.png"));

    static Game& getInstance();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
  private:
    Game();
    ~Game();
    static Game* instance;
};

#endif