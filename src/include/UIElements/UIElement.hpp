#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include "SFML/Graphics.hpp"

class UIElement {
    public:
        virtual void draw(sf::RenderWindow &window);
        virtual void setPosition(float x, float y);
        virtual sf::Vector2f getPosition();
        virtual sf::Vector2u getSize();
        virtual void scale(float x, float y);
};

#endif