#ifndef TEXTANIMATION_HPP
#define TEXTANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>

#include "System/Game.hpp"
#include "Global/Utility.hpp"
#include "Animations/Animation.hpp"

enum AnimationPath {
    Spot,
    Left,
    Right,
    Up,
    Down,
    Parabel
};

class TextFading {
    public:
      TextFading();
      TextFading(std::string text, sf::Vector2f pos, sf::Color textColor, int textSize, sf::Font _font, int _millSecToLive);
      sf::Font font;
      sf::Text text;
      int remainingVisibilty = 0;
      int millSecToLive = 600;
      AnimationPath animationPath = Right;
      float pixelPerMillSec = 0.15;
      // Used for parabel computation
      int pastMillSec = 0;
      float initPosY;
      float initPosX;

      void draw();
      float computeParabel(float value);
      void setNewParabelPos();

    private:

};

class TextFadingManager: Animation {
    public:
        void run();
        void startAnimation(std::string text, sf::Vector2f pos, sf::Color textColor, int textSize, AnimationPath animationPath, int millSecToLive);
        void updateAnimationState();
        TextFading fadingText;
        bool isRunning = false;
};

#endif