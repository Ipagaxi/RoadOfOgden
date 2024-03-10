#ifndef TEXTANIMATION_HPP
#define TEXTANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>

#include "GameState.hpp"
#include "Defines.hpp"
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
        TextFading(std::string text, sf::Vector2f pos, sf::Color textColor, int textSize, sf::Font _font, float _pixelPerMillSec);
        sf::Font font;
        sf::Text text;
        int remainingVisibilty = 0;
        int millSecToLive = 600;
        AnimationPath animationPath = Right;
        float pixelPerMillSec = 0.2;
        // Used for parabel computation
        int pastMillSec = 0;
        float initPosY;
        float initPosX;

        void draw(GameState &gameState);
        float computeParabel(float value);
        void setNewParabelPos();

    private:

};

class TextFadingManager: Animation {
    public:
        void run(GameState &gameState);
        void startAnimation(GameState &gameState, std::string text, sf::Vector2f pos, sf::Color textColor, int textSize, float pixelPerMillSec, AnimationPath animationPath);
        void updateAnimationState(GameState &gameState);
        TextFading fadingText;
        bool isRunning = false;
};

#endif