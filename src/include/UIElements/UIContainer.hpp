#ifndef UICONTAINER_HPP
#define UICONTAINER_HPP

#include "UIElements/UIElement.hpp"

class UIContainer : UIElement {
    private: 

    public:
        void draw(sf::RenderWindow &window);
        void setPosition(float x, float y);
        sf::Vector2u getSize();

    UIContainer();
};

#endif