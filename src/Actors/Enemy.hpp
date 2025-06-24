#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Actors/Actor.hpp"
#include "UIElements/UIColorPicker.hpp"

class Enemy: public Actor {
  public:
    Enemy();
    Enemy(std::string name, int health, int attackStrength, RGB defense, std::string picPath, std::string colorPicPath, std::string colorPicBorderPath);

    void init();

    int get_level();

    void set_level(int level);

    std::string colorPicPath;
    std::string colorPicBorderPath;

  private:
    int level = 1;

};

#endif