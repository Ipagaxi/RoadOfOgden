#include <iostream>

#include "GameState.hpp"
#include "SFML/Graphics.hpp"
#include "ActivityManager.hpp"



int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PnC ");
    window.setFramerateLimit(60);

    ActivityEnum activity = Fight;
    GameState gameState = GameState(window, Fight);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        ActivityManager::runCurrentActivity(gameState);
        window.display();
        
    }
    return 0;
}