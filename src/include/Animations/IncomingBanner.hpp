#ifndef INCOMINGBANNER_HPP
#define INCOMINGBANNER_HPP

#include <string>
#include <SFML/Graphics.hpp>

#include "GameState.hpp"

class IncomingBanner {
    public:
        IncomingBanner(GameState &GameState);
        IncomingBanner(GameState &gameState, std::string label);

        void setNewLabel(std::string newLabel);
        void startAnimation();
        void updateAnimation(GameState &gameState, bool &animationRuns);
        void drawAnimation(sf::RenderWindow &gameWindow);

    private:
        sf::RectangleShape banner;
        sf::Text bannerText;
        void init(GameState &gameState);
};

#endif