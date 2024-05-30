#include "Actors/Player.hpp"

Player::Player() {
    this->name = "None";
    this->health = 0;
    this->attackStrength = 0;
    this->defense = {0, 0, 0};
    this->picPath = "default_actor_quer.png";
}

Player::Player(std::string _name, int _health, int _attackStrength, RGB _defense, std::string _picFilePath) {
    this->name = _name;
    this->health = _health;
    this->attackStrength = _attackStrength;
    this->defense = _defense;
    this->picPath = _picFilePath;
}

void Player::notify(int newValue) const {
    std::cout << "Got a notification" << std::endl;
}
