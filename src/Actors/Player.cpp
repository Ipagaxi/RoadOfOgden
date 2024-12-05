#include "Actors/Player.hpp"

Player::Player() {
    this->name = "None";
    this->health = 0;
    this->attackStrength = 0;
    this->defense = {0, 0, 0};
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