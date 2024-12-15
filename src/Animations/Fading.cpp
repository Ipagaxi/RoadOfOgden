#include "Animations/Fading.hpp"

Fading::Fading(unsigned char _ending_transparency, unsigned char _starting_transparency, int _fading_time_mill_sec) {
  this->ending_transparency = _ending_transparency;
  this->starting_transparency = _starting_transparency;
  this->current_transparency = _starting_transparency;
  this->visibility_range = this->ending_transparency - this->starting_transparency;
  this->fading_time_mill_sec = _fading_time_mill_sec;
}

unsigned char Fading::fade() {
  if (this->past_mill_sec < this->fading_time_mill_sec) {
    Game& game = Game::getInstance();
    float past_ratio = game.gameStatus.elapsedTime.asMilliseconds() / static_cast<float>(this->fading_time_mill_sec);
    int visRatio = int(this->visibility_range * past_ratio);
    this->current_transparency += visRatio;

    this->past_mill_sec += game.gameStatus.elapsedTime.asMilliseconds();
  }
  return this->current_transparency;
}