#include "Actors/Enemy.hpp"

Enemy::Enemy() {
    this->name = "None";
    this->health = 1;
    this->attackStrength = 0;
    this->defense = {0, 0, 0};
    this->picPath = "default_actor_quer.png";
    this->colorPicPath = "color_test.png";
    this->colorPicBorderPath = "color_picker_border.png";
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


void Enemy::init() {

}