#include <iostream>

#include "GameState.hpp"
#include "SFML/Graphics.hpp"
#include "ActivityManager.hpp"
#include "Activities/FightActivity.hpp"
#include "Activities/MenuActivity.hpp"



int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PnC ");
    window.setFramerateLimit(60);

    ActivityEnum activity = Fight;
    GameState gameState = GameState(window, Fight);

    std::unique_ptr<FightActivity> fight = std::make_unique<FightActivity>();
    std::unique_ptr<MenuActivity> menu = std::make_unique<MenuActivity>();
    gameState.setCurrentActivity(std::move(menu));

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        gameState.currentActivity->displayActivity(gameState);
        //gameState.setCurrentActivity(std::move(menu));
        //gameState.performActivity();
        //ActivityManager::runCurrentActivity(gameState);
        window.display();
    }
    return 0;
}