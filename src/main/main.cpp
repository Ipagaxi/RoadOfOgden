#include <iostream>

#include "GameState.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Activities/FightActivity.hpp"
#include "Activities/MenuActivity.hpp"
#include "GenerateColorIMG.hpp"


void setCurrentActivity(std::unique_ptr<Activity> newActivity) {
  std::unique_ptr<Activity> currentActivity = std::move(newActivity);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(), "Road of Ogden", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    ActivityEnum activity = Fight;
    GameState gameState = GameState(window, Fight);

    sf::Vector2i mousePos;            
    sf::Vector2f mousePosF;

    //generateTexture();

    std::unique_ptr<Activity> currentActivity = std::make_unique<MenuActivity>(gameState);

    sf::Clock clock;
    sf::Time time;

    while (window.isOpen()) {
        sf::Event event;

        time = clock.restart();
        gameState.gameStatus.elapsedTime = time;
        //std::cout << "Elapsed Time: " << std::to_string(time.asMilliseconds()) << std::endl;

        while (window.pollEvent(event)) {

            switch (event.type) {
            case sf::Event::Closed:
                //gameState.backgroundMusic.stop();
                window.close();
                break;

            case sf::Event::MouseMoved:
                gameState.gameEvents.mouseMoved = true;
                break;

            case sf::Event::MouseButtonPressed:
                gameState.gameEvents.mousePressed = true;
                mousePos = sf::Mouse::getPosition(window);
                mousePosF = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                gameState.gameEvents.pressedPos = mousePosF;
                break;

            case sf::Event::MouseButtonReleased:
                gameState.gameEvents.mouseReleased = true;
                mousePos = sf::Mouse::getPosition(window);
                mousePosF = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                gameState.gameEvents.releasedPos = mousePosF;
                break;

            default:
                break;
            }
        }
        window.clear();
        currentActivity->executeActivity(gameState);
        window.display();
        gameState.gameEvents.mousePressed = false;
        gameState.gameEvents.mouseReleased = false;
        gameState.gameEvents.mouseMoved = false;
    }
    return 0;
}