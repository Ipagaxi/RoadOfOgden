#include "Actors/Enemy.hpp"

Enemy::Enemy() {
    this->name = "None";
    this->health = 0;
    this->attackStrength = 0;
    this->defense = {0, 0, 0};
    this->picPath = "hamster.png";
    this->colorPicPath = "colorPIC_gen.png";
    this->colorPicBorderPath = "borderMetal.png";
}

Enemy::Enemy(std::string _name, int _health, int _attackStrength, RGB _defense, std::string _picPath, std::string _colorPicPath, std::string _colorPicBorderPath) {
    this->name = _name;
    this->health = _health;
    this->attackStrength = _attackStrength;
    this->defense = _defense;
    this->picPath = _picPath;
    this->colorPicPath = _colorPicPath;
    this->colorPicBorderPath = _colorPicBorderPath;
}