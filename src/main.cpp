#include <iostream>

#include "GameState.hpp"
#include "SFML/Graphics.hpp"
#include "ActivityManager.hpp"
#include "Activities/FightActivity.hpp"



int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PnC ");
    window.setFramerateLimit(60);

    ActivityEnum activity = Fight;
    GameState gameState = GameState(window, Fight);
    std::unique_ptr<FightActivity> fight = std::make_unique<FightActivity>();

    gameState.setCurrentActivity(std::move(fight));

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        gameState.curActivity->displayActivity(gameState);
        //ActivityManager::runCurrentActivity(gameState);
        window.display();
    }
    return 0;
}