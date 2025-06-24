#include "Actors/Actor.hpp"

Actor::Actor() {}

void Actor::set_name(std::string new_name) {
    this->name = new_name;
    this->notify(*this);
}

void Actor::set_health(int new_health) {
    this->health = new_health;
    this->notify(*this);
}

void Actor::set_attack_strength(int new_attack_strength) {
    this->attackStrength = new_attack_strength;
    this->notify(*this);
}

void Actor::set_defense(RGB new_defense) {
    this->defense = new_defense;
    this->notify(*this);
}

void Actor::set_pic_path(std::string new_pic_path) {
    this->picPath = new_pic_path;
    this->notify(*this);
}

std::string Actor::get_name() {
    return this->name;
}

int Actor::get_health() {
    return this->health;
}

int Actor::get_attack_strength() {
    return this->attackStrength;
}

RGB Actor::get_defense() {
    return this->defense;
}

std::string Actor::get_pic_path() {
    return this->picPath;
}