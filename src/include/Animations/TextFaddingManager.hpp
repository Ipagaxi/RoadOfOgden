#ifndef TEXTANIMATION_HPP
#define TEXTANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>

#include "GameState.hpp"
#include "Defines.hpp"
#include "Animations/Animation.hpp"

enum AnimationPaths {
    Spot,
    Left,
    Right,
    Up,
    Down
};

class TextFadding {
    public:
        TextFadding();
        TextFadding(std::string text, sf::Vector2f pos, sf::Color textColor, int textSize, sf::Font _font, float _pixelPerMillSec);
        sf::Font font;
        sf::Text text;
        int remainingVisibilty = 255;
        int millSecToLive = 1000;
        AnimationPaths animationPath = Right;
        float pixelPerMillSec = 0.1;

        void draw(GameState &gameState);

    private:

};

class TextFaddingManager: Animation {
    public:
        void run(GameState &gameState);
        void startAnimation(GameState &gameState, std::string text, sf::Vector2f pos, sf::Color textColor, int textSize, float pixelPerMillSec);
        void updateAnimationState(GameState &gameState, TextFadding &faddingText);
        TextFadding faddingText;
};

#endif