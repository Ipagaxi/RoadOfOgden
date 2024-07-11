#ifndef UIPLAYEROVERVIEW_HPP
#define UIPLAYEROVERVIEW_HPP

#include <SFML/Graphics.hpp>

#include "System/Game.hpp"
#include "UIElements/UIBox.hpp"
#include "UIElements/UIBorderedImage.hpp"
#include "UIElements/UIStats.hpp"

class UIPlayerOverview {
  public:
  UIPlayerOverview(std::shared_ptr<Player> player);

  UIBorderedImage playerFrame;
    Player player;

    void init();
    void changeHealth(int value);
    void draw();

  private:
    UIBox backgroundBox = UIBox(sf::Color(51, 25, 0, 150), "borders/metal_border_900x900.png");
    sf::Texture playerBackgroundTX;
    sf::Sprite playerBackgroundSP;
    UIStats uiPlayerStats;
};

#endif