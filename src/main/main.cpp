#include <iostream>

#include "GameState.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Activities/FightActivity.hpp"
#include "Activities/MenuActivity.hpp"
#include "GenerateColorIMG.hpp"



int main()
{
    sf::RenderWindow window(sf::VideoMode(), "Road of Ogden", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    ActivityEnum activity = Fight;
    GameState gameState = GameState(window, Fight);

    sf::Vector2i mousePos;            
    sf::Vector2f mousePosF;

    //generateTexture();

    std::unique_ptr<MenuActivity> menu = std::make_unique<MenuActivity>(gameState);
    gameState.setCurrentActivity(std::move(menu));

    sf::Clock clock;
    sf::Time time;

    while (window.isOpen()) {
        sf::Event event;

        time = clock.restart();
        gameState.elapsedTime = time;
        //std::cout << "Elapsed Time: " << std::to_string(time.asMilliseconds()) << std::endl;

        while (window.pollEvent(event)) {

            switch (event.type) {
            case sf::Event::Closed:
                //gameState.backgroundMusic.stop();
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
        window.clear();
        gameState.currentActivity->executeActivity(gameState);
        window.display();
        gameState.mousePressed = false;
        gameState.mouseReleased = false;
        gameState.mouseMoved = false;
    }
    return 0;
}