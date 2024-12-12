#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <string>
#include <list>

#include "ObserverPattern/Observer.hpp"

struct RGB {
    int red = 0;
    int green = 0;
    int blue = 0;
};


class Actor: public Subject<Actor> {
  public:

    void set_name(std::string new_name);
    void set_health(int new_health);
    void set_attack_strength(int new_attack_strength);
    void set_defense(RGB new_defense);
    void set_pic_path(std::string);

    std::string get_name();
    int get_health();
    int get_attack_strength();
    RGB get_defense();
    std::string get_pic_path();

    Actor();
  protected:
    std::string name;
    int health;
    int attackStrength;
    RGB defense;

    std::string picPath;

};

#endif