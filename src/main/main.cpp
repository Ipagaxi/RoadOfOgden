#include <iostream>

#include "Game.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Activities/FightActivity.hpp"
#include "Activities/MenuActivity.hpp"
#include "GenerateColorIMG.hpp"
#include "ActivityEnum.hpp"


std::unique_ptr<Activity> setCurrentActivity(Game &game, ActivityEnum newActivityEnum) {
  std::unique_ptr<Activity> newActivity;
  switch (newActivityEnum) {
    case ActivityEnum::Menu:
      newActivity = std::move(std::make_unique<MenuActivity>(game));
      break;
    case ActivityEnum::Fight:
      newActivity = std::move(std::make_unique<FightActivity>(game));
      break;
    case ActivityEnum::Character:
      newActivity = std::move(std::make_unique<CharacterManagementActivity>(game));
      break;
    default:
      break;
  }
  return newActivity;
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(), "Road of Ogden", sf::Style::Fullscreen);
  window.setFramerateLimit(60);

  Game game = Game(window, Fight);

  sf::Vector2i mousePos;
  sf::Vector2f mousePosF;

  //generateTexture();

  std::unique_ptr<Activity> currentActivity = std::make_unique<MenuActivity>(game);
  ActivityEnum currentActivityEnum = ActivityEnum::Menu;
  ActivityEnum oldActivityEnum = ActivityEnum::Menu;

  sf::Clock clock;
  sf::Time time;

  while (window.isOpen()) {
    sf::Event event;

    time = clock.restart();
    game.gameStatus.elapsedTime = time;
    //std::cout << "Elapsed Time: " << std::to_string(time.asMilliseconds()) << std::endl;

    while (window.pollEvent(event)) {

        switch (event.type) {
        case sf::Event::Closed:
            //game.backgroundMusic.stop();
            window.close();
            break;

        case sf::Event::MouseMoved:
          game.gameEvents.mouseMoved = true;
            break;

        case sf::Event::MouseButtonPressed:
          game.gameEvents.mousePressed = true;
            mousePos = sf::Mouse::getPosition(window);
            mousePosF = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            game.gameEvents.pressedPos = mousePosF;
            break;

        case sf::Event::MouseButtonReleased:
          game.gameEvents.mouseReleased = true;
            mousePos = sf::Mouse::getPosition(window);
            mousePosF = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            game.gameEvents.releasedPos = mousePosF;
            break;

        default:
            break;
        }
    }
    window.clear();
    currentActivityEnum = currentActivity->executeActivity(game);
    if (currentActivityEnum != oldActivityEnum) {
      currentActivity = std::move(setCurrentActivity(game, currentActivityEnum));
      oldActivityEnum = currentActivityEnum;
    }
    window.display();
    game.gameEvents.mousePressed = false;
    game.gameEvents.mouseReleased = false;
    game.gameEvents.mouseMoved = false;
  }
  return 0;
}