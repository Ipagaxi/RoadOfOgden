#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Actors/Actor.hpp"
#include "Items/Item.hpp"

class Player: public Actor {

  public:
    
    void set_level(int new_level);
    void set_experience(int new_experience);
    void set_equipped_items(std::vector<Item> new_equipped_items);
    void set_inventory_items(std::vector<Item> new_inventory_items);

    int get_level();
    int get_experience();
    std::vector<Item> get_equipped_items();
    std::vector<Item> get_inventory_items();

    Player();
    Player(std::string name, int level, int experience, std::string picFilePath);

  private:
    int level;
    int experience;

    std::vector<Item> equipped_items;
    std::vector<Item> inventory_items;


};

#endif