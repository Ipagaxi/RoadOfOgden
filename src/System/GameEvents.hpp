#ifndef GAMEEVENTS_HPP
#define GAMEEVENTS_HPP

#include "SFML/Graphics.hpp"

class GameEvents {
  public:
    GameEvents();

    bool mouseMoved;
    bool mousePressed;
    bool mouseReleased;

    sf::Vector2f pressedPos;
    sf::Vector2f releasedPos;
};

#endif