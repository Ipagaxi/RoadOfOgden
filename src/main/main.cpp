#include <iostream>

#include "GameState.hpp"
#include "SFML/Graphics.hpp"
#include "Activities/FightActivity.hpp"
#include "Activities/MenuActivity.hpp"



int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "PnC ");
    window.setFramerateLimit(60);

    ActivityEnum activity = Fight;
    GameState gameState = GameState(window, Fight);

    sf::Vector2i mousePos;            
    sf::Vector2f mousePosF;

    std::unique_ptr<FightActivity> fight = std::make_unique<FightActivity>();
    std::unique_ptr<MenuActivity> menu = std::make_unique<MenuActivity>();
    gameState.setCurrentActivity(std::move(fight));

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseMoved:
                gameState.mouseMoved = true;
                break;

            case sf::Event::MouseButtonPressed:
                gameState.mousePressed = true;
                mousePos = sf::Mouse::getPosition(window);
                mousePosF = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                gameState.pressedPos = mousePosF;
                break;

            case sf::Event::MouseButtonReleased:
                gameState.mouseReleased = true;
                mousePos = sf::Mouse::getPosition(window);
                mousePosF = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                gameState.releasedPos = mousePosF;
                break;

            default:
                break;
            }
        }
        if (gameState.mousePressed) {
            std::cout << "Pressed" << std::endl;
        }
        if (gameState.mouseReleased) {
            std::cout << "Released" << std::endl;
        }
        window.clear();
        gameState.currentActivity->executeActivity(gameState);
        window.display();
        gameState.mousePressed = false;
        gameState.mouseReleased = false;
        gameState.mouseMoved = false;
    }
    return 0;
}