#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Defines.hpp"
#include "GameState.hpp"

class UIButton {
    private:
        bool hovered;
        bool pressed;

        sf::Texture basicTX;
        sf::Texture clickedTX;
        sf::Texture hoveredTX;
        sf::Sprite buttonSP;

        void hoverListener(GameState &gameState);

        bool buttonContainsMouse(GameState &gameState);



    public:
        sf::Font font;
        sf::Text label;

        UIButton();
        UIButton(std::string labelText, std::string fileName, float x, float y);

        bool clicked(GameState &gameState);

        void setPosition(float x, float y);
        sf::Vector2u getSize();

        void drawButton(GameState &gameState);
};

#endif