#include "Actors/Player.hpp"

Player::Player() {
    this->name = "Albert";
    this->level = 1;
    this->experience = 0;
    this->health = 70;
    this->attackStrength = 10;
    this->defense = {100, 100, 100};

    this->equipped_items = {};
    this->inventory_items = {};

    this->picPath = "default_actor_quer.png";
}

Player::Player(std::string _name, int _level, int _experience, std::string _picFilePath) {
    this->name = _name;
    this->level = _level;
    this->experience = _experience;

    this->health = 70 + _level * 5;
    this->attackStrength = 10 + _level;
    this->defense = {100, 100, 100};
    this->picPath = _picFilePath;
}

void Player::set_level(int new_level) {
    this->level = new_level;
    this->notify(*this);
}

void Player::set_experience(int new_experience) {
    this->experience = new_experience;
    this->notify(*this);
}
void Player::set_equipped_items(std::vector<Item> new_equipped_items) {
    this->equipped_items = new_equipped_items;
    this->notify(*this);
}

void Player::set_inventory_items(std::vector<Item> new_inventory_items) {
    this->inventory_items = new_inventory_items;
    this->notify(*this);
}

int Player::get_level() {
    return this->level;
}

int Player::get_experience() {
    return this->experience;
}

std::vector<Item> Player::get_equipped_items() {
    return this->equipped_items;
}

std::vector<Item> Player::get_inventory_items() {
    return this->inventory_items;
}