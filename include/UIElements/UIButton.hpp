#ifndef UIBUTTON_HPP
#define UIBUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "Defines.hpp"

class UIButton {
    private:
        sf::Texture basicTX;
        sf::Texture clickedTX;
        sf::Texture hoveredTX;

    public:
        UIButton(std::string fileName);
};

#endif