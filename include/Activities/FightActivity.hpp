#ifndef FIGHTACTIVITY_HPP
#define FIGHTACTIVITY_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Activities/Activity.hpp"


class FightActivity: public Activity {
    std::string nameEnemy = "Enemy";
  public:
    void displayActivity(sf::RenderWindow &window, sf::Texture &background, sf::Texture &gear) override;
};

#endif