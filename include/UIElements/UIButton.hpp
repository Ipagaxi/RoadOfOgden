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



    public:
        sf::Sprite buttonSP;

        UIButton();
        UIButton(std::string fileName, float x, float y);

        void hoverListener(GameState &gameState);
        bool clicked(GameState &gameState);
};

#endif