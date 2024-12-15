#ifndef FADING_HPP
#define FADING_HPP

#include <SFML/Graphics.hpp>
#include "System/Game.hpp"

class Fading {
  private:
    unsigned char ending_transparency = 255;
    unsigned char starting_transparency = 0;
    int visibility_range;
    int current_transparency;
    int fading_time_mill_sec = 500;
    int past_mill_sec = 0;

  public:
    Fading(unsigned char max_transparency, unsigned char min_transparency, int fading_time_mill_sec);
    unsigned char fade();

};

#endif