#ifndef UICOMPONENT_HPP
#define UICOMPONENT_HPP

#include <SFML/Graphics.hpp>

class UIComponent {
    private:

    public:
        virtual void draw(sf::RenderWindow &gameWindow);
        virtual sf::Vector2f getPosition();
        virtual void setPosition(float x, float y);
        virtual sf::FloatRect getSize();
};

#endif