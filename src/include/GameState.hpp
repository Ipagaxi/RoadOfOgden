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

class GameState {
  public:
    std::unique_ptr<Activity> currentActivity;
    bool mouseMoved;
    bool mousePressed;
    bool mouseReleased;

    sf::Vector2f pressedPos;
    sf::Vector2f releasedPos;
    sf::Font mainFont;
    sf::Music backgroundMusic;
    sf::RenderWindow* gameWindow;

    Player player = Player("Ipagaxi", 20, 12, {100, 100, 100});

    GameState(sf::RenderWindow &window, ActivityEnum activity);

    void setCurrentActivity(std::unique_ptr<Activity> newActivity);
};

#endif