#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include "SFML/Graphics.hpp"

class UIElement {
    public:
        virtual void draw();
        virtual void setPosition(float x, float y);
        virtual sf::Vector2f getPosition();
        virtual sf::FloatRect getSize();
        virtual void scale(float x, float y);
};

#endif