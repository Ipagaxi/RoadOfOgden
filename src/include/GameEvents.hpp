#ifndef GAMEEVENTS_HPP
#define GAMEEVENTS_HPP

class GameEvents {
  public:
    bool mouseMoved;
    bool mousePressed;
    bool mouseReleased;

    sf::Vector2f pressedPos;
    sf::Vector2f releasedPos;
};

#endif