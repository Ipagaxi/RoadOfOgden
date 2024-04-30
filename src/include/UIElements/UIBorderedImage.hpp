#ifndef UIBORDEREDIMAGE_HPP
#define UIBORDEREDIMAGE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Game.hpp"
#include "UIElements/UIElement.hpp"
#include "Defines.hpp"

class UIBorderedImage: public UIElement {
    public:
        void init(std::string imageFilePath, std::string borderFilePath);
        void setImage(std::string imagePath);
        void draw() override;
        void setPosition(float x, float y) override;
        sf::Vector2f getPosition() override;
        sf::FloatRect getSize() override;
        void scale(float x, float y) override;

    private:
        sf::Texture borderTX;
        sf::Sprite borderSP;
        sf::Texture imageTX;
        sf::Sprite imageSP;
};

#endif
