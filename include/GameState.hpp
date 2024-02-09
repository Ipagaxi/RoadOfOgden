#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Textures.hpp"
#include "ActivityEnum.hpp"

class GameState {
  public:
    ActivityEnum currentActivity;
    Textures textures;
    sf::RenderWindow* gameWindow;

    GameState(sf::RenderWindow &window, ActivityEnum activity);
};

#endif